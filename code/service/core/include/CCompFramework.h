#ifndef CCOMPFRAMEWORK_H
#define CCOMPFRAMEWORK_H
#include <unordered_map>
#include <set>
#include <mutex>
#include <queue>
#include <atomic>
#include <memory>
#include <condition_variable>

#include "ComponentExport.h"
#include "IEventHandler.h"
#include "IComponent.h"

#ifdef OS_WIN
#include <Windows.h>
static const char* strLibExtension = ".dll";
#define libHandle HINSTANCE


#elif defined OS_LINUX
#include <dirent.h>
#include <dlfcn.h>
static const char* strLibExtension = ".so";
#define libHandle void*


#endif

BEGINE_NAMESPACE(mmrComp)

template<typename _T>
class WeakPtrCompare {
public:
	bool operator()(std::weak_ptr<_T> t1, std::weak_ptr<_T> t2)const {
		return t1.lock() < t2.lock();
	}
};

class COMPO_CORE_CLASS_API CCompFramework
{
	CCompFramework(){
		m_bRunning.store(false, std::memory_order_relaxed);
	}
	~CCompFramework(){}
public:
	static CCompFramework* getInstance()
	{
		static CCompFramework* instalce = new CCompFramework;
		return instalce;
	}

	bool start();//配置文件路径

	void stop();

	//处理事件相关接口
	void addHandler(std::string strTopic, IEventHandler* pHandler);

	void removeHandler(std::string strTopic, IEventHandler* pHandler);

	void addEvenVartData(mmrUtil::CVarDatas varData);

	//处理组件相关
	bool addComponent(std::unique_ptr<IComponent> pComp);

	//void removeComponet(uint16_t usIndex);

	template<typename _T>
	void registService(std::shared_ptr<_T> pSer) 
	{
		m_mapService.insert(std::make_pair(getTypeID<_T>(), std::move(pSer)));
	}

	template<typename _T>
	std::shared_ptr<_T> getService() 
	{
		auto iterSer = m_mapService.find(getTypeID<_T>());
		if (iterSer != m_mapService.end())
			return std::static_pointer_cast<_T>(iterSer->second);
		else 
			return nullptr;
	}
private:
	void dealThread();

	template<typename _T>
	std::string getTypeID() 
	{
		return typeid(_T).name();
		//return _T::GetGUID();
	}
private:
	std::unique_ptr<std::thread> m_threadDeal;
	std::atomic_bool m_bRunning;

	//处理事件相关成员
	std::unordered_map<std::string, std::set<IEventHandler*>> m_mapHandlers;//所有事件处理者
	std::mutex m_mutexHander;//事件处理集合互斥量

	std::queue<std::pair<std::string, mmrUtil::CVarDatas>> m_queueAddData;
	std::queue<std::pair<std::string, mmrUtil::CVarDatas>> m_queueDealData;
	std::mutex m_mutexData;
	std::condition_variable m_cvData;

	//处理组件相关
	std::unordered_map<uint16_t, std::unique_ptr<IComponent>> m_mapComponents;
	std::map<std::string, std::shared_ptr<void>> m_mapService;//在组件初始化时注册组件，因此不用使用锁
	std::set<libHandle> m_libHandl;
};

template<typename _T>
class CCompRegister//组件自动注册类
{
public:
	CCompRegister() 
	{
		std::unique_ptr<IComponent> compPtr = std::make_unique<_T>();
		CCompFramework::getInstance()->addComponent(std::move(compPtr));
	}
	~CCompRegister() = default;
};


END_NAMESPACE(mmrComp)

#define CoreFrameworkIns mmrComp::CCompFramework::getInstance()

#define REGIST_COMPONENT(_Component) mmrComp::CCompRegister<_Component> g_Comp

#endif