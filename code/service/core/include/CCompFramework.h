#ifndef CCOMPFRAMEWORK_H
#define CCOMPFRAMEWORK_H
#include <unordered_map>
#include <set>
#include <mutex>
#include <queue>
#include <atomic>

#include "ComponentExport.h"
#include "IEventHandler.h"
#include "IComponent.h"

BEGINE_NAMESPACE(mmrComp)

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

	bool start(std::string strConfigPath);//配置文件路径

	void stop();

	//处理事件相关接口
	void registHandler(std::string strTopic, IEventHandler* pHandler);

	void removeHandler(std::string strTopic, IEventHandler* pHandler);

	void addEvent(std::string strTopic, mmrUtil::CVarDatas varData);

	//处理组件相关
	bool addComponent(IComponent* pComp);

	void removeComponet(IComponent* pComp);

	template<typename _T>
	void registService(_T* pSer) 
	{
		const auto& tpInfo = typeid(_T);
		m_mapService.insert(std::make_pair(tpInfo.name(), static_cast<void*>(pSer)));
	}

	template<typename _T>
	_T* getService() 
	{
		auto iterSer = m_mapService.find(typeid(_T).name());
		if (iterSer != m_mapService.end())
			return static_cast<_T*>(iterSer->second);
		else 
			return nullptr;
	}
private:
	void dealThread();

private:
	std::unique_ptr<std::thread> m_threadDeal;
	std::atomic_bool m_bRunning;

	//处理事件相关成员
	std::unordered_map<std::string, std::set<IEventHandler*>> m_mapHandlers;//所有事件处理者
	std::mutex m_mutexHander;//事件处理集合互斥量

	std::queue<std::pair<std::string, mmrUtil::CVarDatas>> m_queueAddData;
	std::queue<std::pair<std::string, mmrUtil::CVarDatas>> m_queueDealData;
	std::mutex m_mutexData;

	//处理组件相关
	std::unordered_map<uint16_t, IComponent*> m_mapComponents;
	//std::map<const std::type_info&, void*> m_mapService;//在组件初始化时注册组件，因此不用使用锁
	std::map<std::string, void*> m_mapService;//在组件初始化时注册组件，因此不用使用锁
	//std::mutex m_mutexComp;

	
};

END_NAMESPACE(mmrComp)

#define CoreFrameworkIns mmrComp::CCompFramework::getInstance()

#endif