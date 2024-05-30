#include "CCompFramework.h"

#include "util/json.hpp"
#include "util/UtilFunc.h"

#include <sstream>
#include <fstream>
#include <iostream>

mmrComp::CCompFramework::CCompFramework()
	:m_loggerCtrl(std::make_unique<CLoggerCtrl>())
{
	m_bRunning.store(false, std::memory_order_relaxed);
}

mmrComp::CCompFramework::~CCompFramework()
{

}
bool mmrComp::CCompFramework::start()
{
	if (m_bRunning.load(std::memory_order_relaxed))
	{
		LOG_WARN("component has been started!");
		return false;
	}

	try
	{
		//启动日志
		logInstancePtr->start();

		//启动处理线程
		m_bRunning.store(true, std::memory_order_relaxed);
		m_threadDeal = std::make_unique<std::thread>(&CCompFramework::dealThread, this);

		//读配置文件，加载所有组件
		std::string strAppPath, strAppName;
		mmrUtil::getAppPathAndName(strAppPath, strAppName);
		std::string strConfigPath = strAppPath + "config/serviceApp.json";

		Json::Value jsonRoot;
		std::string strErr = Json::json_from_file(strConfigPath, jsonRoot);

		if (jsonRoot.IsNull() || !strErr.empty())
		{
			LOG_ERROR_PRINT("parse json file [%s] failed! error message is: %s.", strConfigPath.c_str(), strErr.c_str());
			return false;
		}

		auto components = jsonRoot["Components"];
		if (components.IsNull())
		{
			LOG_ERROR_PRINT("config file [%s] do not has key [Components] !", strConfigPath.c_str());
			return false;
		}

		for (const auto& iterComp : components.ObjectRange())
		{
#ifdef OS_WIN
			std::string strLibPath = strAppPath + "component/" + iterComp.first + ".dll";
			HINSTANCE handle = LoadLibrary(strLibPath.c_str());
			if (handle == nullptr)
			{
				FreeLibrary(handle);
			}
#elif defined OS_LINUX
			std::string strLibPath = strAppPath + "component/lib" + iterComp.first + ".so";
			void* handle = dlopen(strLibPath.c_str(), RTLD_LAZY);
			if (handle == nullptr)
			{
				dlclose(handle);
			}
#endif
			else
			{
				m_libHandl.insert(handle);
			}
		}
		//初始化所有组件
		for (const auto& iterComp : m_mapComponents)
		{
			std::string strComoName = iterComp.second->getName();
			if (!components.hasKey(strComoName))
			{
				LOG_ERROR_PRINT("component name [%s] do not find in config file!", strComoName.c_str());
				continue;

			}
			if (!iterComp.second->initialise(components[strComoName]))
			{
				LOG_ERROR_PRINT("init component name [%s] failed!", strComoName.c_str());
				continue;
			}
		}

		for (const auto& iterComp : m_mapComponents)
		{
			if (!iterComp.second->start())
			{
				LOG_ERROR_PRINT("component [%s] start failed!", iterComp.second->getName());
			}
		}

		LOG_INFO("framework start success ....");
		printf("framework start success ....\n\n");
	}
	catch (std::exception& e)
	{
		LOG_FATAL("exception info is %s.", e.what());
		return false;
	}
	catch (...)
	{
		LOG_FATAL("unknow exception.");
		return false;
	}

	return true;
}


void mmrComp::CCompFramework::stop()
{
	//停掉线程
	if (true == m_bRunning)
	{
		m_bRunning.store(false, std::memory_order_relaxed);//退出线程
		m_cvData.notify_all();
		if (m_threadDeal->joinable())
		{
			m_threadDeal->join();//等待线程结束
		}
	}

	//停止所有组件
	for (const auto& iterComp : m_mapComponents)
	{
		iterComp.second->stop();
	}

	//在卸载库前，清空从动态库获取的指针数据
	m_mapComponents.clear();

	m_mapService.clear();

	m_loggerCtrl->getMapCtrollerPtr().clear();

	//卸载所有动态库
	for (const auto& iterHandl:m_libHandl)
	{
#ifdef OS_WIN
		FreeLibrary(iterHandl);
#elif defined OS_LINUX
		dlclose(iterHandl);
#endif
	}

	//清空数据
	//m_mapHandlers.clear();不用清空，析构函数自动移除

	while (m_queueDealData.size() > 0)
		m_queueDealData.pop();

	while (m_queueDealData.size() > 0)
		m_queueDealData.pop();

	m_libHandl.clear();

	LOG_INFO("framework stoped!");
}

void mmrComp::CCompFramework::addHandler(std::string strTopic,IEventHandler* pHandler)
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

void mmrComp::CCompFramework::addEvenVartData(mmrUtil::CVarDatas varData)
{
	std::unique_lock<std::mutex> lock(m_mutexData);
	m_queueAddData.emplace(std::make_pair(varData.getName(), std::move(varData)));
	m_cvData.notify_all();
}

void mmrComp::CCompFramework::dealThread()
{
	while (m_bRunning.load(std::memory_order_relaxed))
	{
		if (m_queueAddData.size() > 0)
		{
			LOG_INFO("Begine to deal event ,size[%d]", m_queueAddData.size());

			{//交换数据
				std::lock_guard<std::mutex> lock(m_mutexData);
				std::swap(m_queueAddData, m_queueDealData);
			}

			{//处理数据
				std::lock_guard<std::mutex> lock(m_mutexHander);
				while (m_queueDealData.size() > 0)
				{
					const auto& data = m_queueDealData.front();

					auto iterMap = m_mapHandlers.find(data.first);
					if (iterMap != m_mapHandlers.end())
					{
						for (const auto iterHandler : iterMap->second)
						{
							iterHandler->handleEvent(data.second);
						}
					}
					m_queueDealData.pop();
				}
			}
		}

		{
			std::unique_lock<std::mutex> lock(m_mutexData);
			while (m_queueAddData.empty() && m_bRunning.load(std::memory_order_relaxed))
			{
				m_cvData.wait_for(lock, std::chrono::seconds(100));
			}
		}
	}

	LOG_INFO("frame work deal thread exit!", m_queueAddData.size());
}

bool mmrComp::CCompFramework::addComponent(std::unique_ptr<IComponent> pComp)
{
	uint16_t usIndex = pComp->getIndex();
	auto iterComp = m_mapComponents.find(usIndex);
	if (iterComp != m_mapComponents.end())
	{
		LOG_ERROR("Component [%s] load failed! it has the same index[%d] whith component [%s].",
			pComp->getName(), usIndex, iterComp->second->getName());
		return false;
	}

	LOG_INFO("Component [%s] index [%d] load succesfully!", pComp->getName(), pComp->getIndex());
	m_mapComponents.insert(std::make_pair(usIndex, std::move(pComp)));
	return true;
}

//void mmrComp::CCompFramework::removeComponet(uint16_t usIndex)
//{
//	//暂不实现
//}

void mmrComp::CCompFramework::addComponetLogWrapper(std::string strCompName, std::weak_ptr<mmrUtil::LogWrapper> logWrap)
{
	m_loggerCtrl->getMapCtrollerPtr().insert(std::make_pair(std::move(strCompName), logWrap));
}



void mmrComp::CCompFramework::loggerCtrlLoop()
{
	m_loggerCtrl->loop();
}



