#include "util/CThreadpool.hpp"

const int TASK_MAX_THRESHHOLD = INT32_MAX;
const int THREAD_MAX_THRESHHOLD = 1024;
const int THREAD_MAX_IDLE_TIME = 60;	//��λ����
int MmrCommon::Thread::m_generateId = 0;

/*
=========Threadʵ��=============
*/
MmrCommon::Thread::Thread(ThreadFunc func)
	:m_func(func)
	, m_threadId(m_generateId++)
{
}

void MmrCommon::Thread::start()
{
	//����һ���߳���ִ��һ���̺߳���
	std::thread t(m_func, m_threadId);
	t.detach();	//�����ػ��߳�
}

int MmrCommon::Thread::getId()const
{
	return m_threadId;
}


/*
========ThreadPoolʵ��==========
*/

#define IS_TRUE_RETURN(bValue)\
if (true == bValue)\
{\
	return;\
}


MmrCommon::ThreadPool::ThreadPool()
	:m_initThreadSize(std::thread::hardware_concurrency())
	, m_taskSize(0)
	, m_idleThreadSize(0)
	, m_curThreadSize(0)
	, m_taskqueMaxThresHold(TASK_MAX_THRESHHOLD)
	, m_threadSizeThreshHold(THREAD_MAX_THRESHHOLD)
	, m_poolMode(PoolMode::MODE_FIXED)
	, m_isPoolRunning(false)
{
}

MmrCommon::ThreadPool::~ThreadPool()
{
	if (true == m_isPoolRunning)
	{
		try { stop(); }
		catch (...) 
		{
			//LOGFATAL("[%s][%d] stop Thread pool failed!" ,__STRING_FUNCTION__ , __LINE__);
			std::abort();
		}
		
	}
}

void MmrCommon::ThreadPool::setMode(PoolMode mode)
{
	IS_TRUE_RETURN(m_isPoolRunning)
	m_poolMode = mode;
}

void MmrCommon::ThreadPool::setTaskQueMaxThrshHold(const uint32_t& threshhold)
{
	IS_TRUE_RETURN(m_isPoolRunning)
	m_taskqueMaxThresHold = threshhold;
}

void MmrCommon::ThreadPool::setThreadSizeThreshHold(const uint16_t& threshHold)
{
	IS_TRUE_RETURN(m_isPoolRunning)
	if (m_poolMode == PoolMode::MODE_CACHED)
		m_threadSizeThreshHold = threshHold;
}

void MmrCommon::ThreadPool::setThreadSize(const uint16_t& treadSize)
{
	IS_TRUE_RETURN(m_isPoolRunning)
	if (treadSize < 0) 
	{
		return;
	}
	//��¼��ʼ�̳߳صĸ���
	m_initThreadSize = treadSize > m_initThreadSize ? m_initThreadSize : treadSize;
	m_curThreadSize = m_initThreadSize;
}

void MmrCommon::ThreadPool::threadFunc(int threadId)
{
	auto lastTime = std::chrono::high_resolution_clock().now();

	//�����������ִ����ɣ��̳߳ز��ܻ��������߳���Դ
	while (true)
	{
		Task task;
		{
			//��ȡ��
			std::unique_lock<std::mutex> lock(m_taskQueMtx);
			//LOGDEBUG_BYSTREAM("["<< __STRING_FUNCTION__ <<"]["<< __LINE__ <<"] Thread ID:" << std::this_thread::get_id() << " is trying to get task!");
			//std::cout << "tid:" << std::this_thread::get_id() << "���ڳ��Ի�ȡ����" << std::endl;
			// cachedģʽ�£��п����Ѿ������˺ܶ���̣߳����ǿ���ʱ�䳬��60s��Ӧ�ðѶ�����߳�
			// �������յ�������initThreadSize_�������߳�Ҫ���л��գ�
			// ��ǰʱ�� - ��һ���߳�ִ�е�ʱ�� > 60s

			// ÿһ���з���һ��   ��ô���֣���ʱ���أ������������ִ�з���
			// �� + ˫���ж�
			while (m_taskque.size() == 0)
			{
				//�̳߳�Ҫ���� �����߳���Դ
				if (!m_isPoolRunning)
				{
					m_threads.erase(threadId);
					//LOGDEBUG_BYSTREAM("[" << __STRING_FUNCTION__ << "][" << __LINE__ << "] Thread ID:" << std::this_thread::get_id() << " exit!");
					//std::cout << "thread id: " << std::this_thread::get_id << " exit" << std::endl;
					m_exitCond.notify_all();
					return;//�̺߳������� 
				}

				if (m_poolMode == PoolMode::MODE_CACHED)
				{
					if (std::cv_status::timeout ==
						m_notEmpty.wait_for(lock, std::chrono::seconds(1)))
					{
						auto now = std::chrono::high_resolution_clock().now();
						auto dur = std::chrono::duration_cast<std::chrono::seconds>(now - lastTime);
						if (dur.count() >= THREAD_MAX_IDLE_TIME
							&& m_curThreadSize > m_initThreadSize)
						{
							// ��ʼ���յ�ǰ�߳�
							// ��¼�߳���������ر�����ֵ�޸�
							// ���̶߳�����߳��б�������ɾ��   û�а취 threadFunc��=��thread����
							// threadid => thread���� => ɾ��
							m_threads.erase(threadId); // std::this_thread::getid()
							m_curThreadSize--;
							m_idleThreadSize--;

							//LOGDEBUG_BYSTREAM("[" << __STRING_FUNCTION__ << "][" << __LINE__ << "] Thread ID:" << std::this_thread::get_id() << " exit!");
							//std::cout << "threadid:" << std::this_thread::get_id() << " exit!"
							//	<< std::endl;
							return;
						}
					}
				}
				else
				{
					//�ȴ�empty����
					m_notEmpty.wait(lock);
				}
			}
			m_idleThreadSize--;
			//LOGDEBUG_BYSTREAM("[" << __STRING_FUNCTION__ << "][" << __LINE__ << "] Thread ID:" << std::this_thread::get_id() << " get task success!");
			//std::cout << "tid:" << std::this_thread::get_id() << "��ȡ����ɹ�" << std::endl;

			//�����������ȡ������
			task = m_taskque.front();
			m_taskque.pop();
			m_taskSize--;

			//�����Ȼ������ ��֪ͨ�����߳�
			if (m_taskque.size() > 0)
			{
				m_notEmpty.notify_all();
			}
			//ȡ��һ���������֪ͨ ֪ͨ���Լ����ύ����
			m_notFull.notify_all();
		}//�����ŵ�

		 //��ǰ�̸߳���ִ���������
		if (task != nullptr)
		{
			task();
		}
		m_idleThreadSize++;
		lastTime = std::chrono::high_resolution_clock().now();
		//LOGDEBUG_BYSTREAM("[" << __STRING_FUNCTION__ << "][" << __LINE__ << "] Thread ID:" << std::this_thread::get_id() << " deal task end!");
	}
}

void MmrCommon::ThreadPool::start()
{
	//�����̳߳�����״̬
	IS_TRUE_RETURN(m_isPoolRunning)

	m_isPoolRunning = true;

	m_idleThreadSize = 0;//�����߳�����Ϊ0

	//�����̶߳���
	for (int i = 0; i < m_initThreadSize; i++)
	{
		auto ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this, std::placeholders::_1));
		//auto ptr = std::unique_ptr<Thread>(new Thread(std::bind(&ThreadPool::threadFunc, this, std::placeholders::_1)));
		int	threadId = ptr->getId();
		m_threads.emplace(threadId, std::move(ptr));
		m_threads[i]->start();
		++m_idleThreadSize;
	}
}

void MmrCommon::ThreadPool::stop()
{
	m_isPoolRunning = false;

	//�ȴ��̳߳��������е��̷߳��� �߳�������״̬ ����������ִ����
	std::unique_lock<std::mutex> lock(m_taskQueMtx);
	m_notEmpty.notify_all();
	m_exitCond.wait(lock, [&]()->bool {return m_threads.size() == 0; });
}

bool MmrCommon::ThreadPool::checkRunningState()const
{
	return m_isPoolRunning;
}

MmrCommon::ThreadPool* MmrCommon::ThreadPool::getThreadPool()
{
	static ThreadPool* pThreadPool = new ThreadPool();
	return pThreadPool;
}