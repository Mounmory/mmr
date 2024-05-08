#include "CCompFramework.h"
#include "util/Clogger.h"

#ifdef OS_WIN
#include <Windows.h>
static const char* strLibExtension = ".dll";
#elif defined OS_LINUX
#include <dirent.h>
#include <dlfcn.h>
static const char* strLibExtension = ".so";
#endif

bool mmrComp::CCompFramework::start(std::string strConfigPath)
{
	if (m_bRunning.load(std::memory_order_relaxed))
	{
		LOG_WARN("component has been started!");
		return false;
	}
	//启动处理线程
	m_bRunning.store(true, std::memory_order_relaxed);
	m_threadDeal = std::make_unique<std::thread>(&CCompFramework::dealThread, this);

	//加载所有组件
#ifdef OS_WIN
	HINSTANCE hDLL = LoadLibrary("D:/VMs/build/bin/RelWithDebInfo/component/CompTest.dll");
	if (hDLL == NULL) 
	{
		FreeLibrary(hDLL);
	}
#elif defined OS_LINUX
	void* handle = dlopen("/home/mmrPro/build/bin/component/libCompTest.so", RTLD_LAZY);
	if (handle == nullptr)
	{
		dlclose(handle);
	}
#endif

	//初始化所有组件
	for (const auto& iterComp : m_mapComponents)
	{
		iterComp.second->initialise();
	}


	LOG_INFO("framework started!");
	return true;
}


void mmrComp::CCompFramework::stop()
{
	//停止所有组件


	//卸载所有动态库

	//停掉线程
	if (true == m_bRunning)
	{
		m_bRunning.store(false,std::memory_order_relaxed);//退出线程
		m_threadDeal->join();//等待线程结束
	}
	LOG_INFO("framework stoped!");
}

void mmrComp::CCompFramework::registHandler(std::string strTopic, IEventHandler* pHandler)
{
	std::lock_guard<std::mutex> lock(m_mutexHander);
	m_mapHandlers[strTopic].insert(pHandler);
}


void mmrComp::CCompFramework::removeHandler(std::string strTopic, IEventHandler* pHandler)
{
	std::lock_guard<std::mutex> lock(m_mutexHander);
	auto iterMap = m_mapHandlers.find(strTopic);
	if (iterMap != m_mapHandlers.end()) 
	{
		iterMap->second.erase(pHandler);
		if (iterMap->second.size() == 0)
		{
			m_mapHandlers.erase(iterMap);
		}
	}
}

void mmrComp::CCompFramework::addEvent(std::string strTopic, mmrUtil::CVarDatas varData)
{
	std::lock_guard<std::mutex> lock(m_mutexData);
	m_queueAddData.emplace(std::make_pair(std::move(strTopic), std::move(varData)));
}

void mmrComp::CCompFramework::dealThread()
{
	while (m_bRunning)
	{
		if (m_queueAddData.size() > 0)
		{
			LOG_INFO("Begine to deal event ,size[%d]", m_queueAddData.size());

			{
				std::lock_guard<std::mutex> lock(m_mutexData);
				std::swap(m_queueAddData, m_queueDealData);
			}

			std::lock_guard<std::mutex> lock(m_mutexHander);
			while (m_queueDealData.size() > 0)
			{
				const auto& data = m_queueDealData.front();

				auto iterMap = m_mapHandlers.find(data.first);
				if (iterMap != m_mapHandlers.end())
				{
					for (const auto iterHandler : iterMap->second)
					{
						iterHandler->handleEvent(data.first, data.second);
					}
				}
				m_queueDealData.pop();
			}
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));//休眠1ms
		}
	}
}

bool mmrComp::CCompFramework::addComponent(IComponent* pComp)
{
	uint16_t usIndex = pComp->getIndex();
	auto iterComp = m_mapComponents.find(usIndex);
	if (iterComp != m_mapComponents.end())
	{
		LOG_ERROR("Component [%s] load failed! it has the same index[%d] whith component [%s].",
			pComp->getName(), usIndex, iterComp->second->getName());
		return false;
	}

	m_mapComponents.insert(std::make_pair(usIndex, pComp));
	LOG_INFO("Component [%s] index [%d] load succesfully!");
	return true;
}

void mmrComp::CCompFramework::removeComponet(IComponent* pComp)
{
	//暂不实现
}
