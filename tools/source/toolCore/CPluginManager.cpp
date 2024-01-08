#include "toolCore/CPluginManager.h"
#include "interface/IToolBase.hpp"
#include <iostream>
#include <vector>
#include <string>

#ifdef OS_WIN
#include <Windows.h>
static const char* strLibExtension = ".dll";
#elif defined OS_LINUX
#include <dirent.h>
#include <dlfcn.h>
static const char* strLibExtension = ".so";
#endif


MmrTools::CPluginManager* MmrTools::CPluginManager::getPluginManager()
{
	static MmrTools::CPluginManager* pluginManager = new MmrTools::CPluginManager;
	return pluginManager;
}

int MmrTools::CPluginManager::loadPuglins(const std::string& strPath)
{
	m_mapTools.clear();
	std::vector<std::string> files;

	//查找文件夹下所有文件
#ifdef OS_WIN
	std::string searchPath = strPath + "/*" + strLibExtension;
	WIN32_FIND_DATA findData;
	HANDLE hFind = FindFirstFile(searchPath.c_str(), &findData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				std::string filePath = strPath + "/" + findData.cFileName;
				files.push_back(filePath);
			}
		} while (FindNextFile(hFind, &findData));

		FindClose(hFind);
	}
#elif defined OS_LINUX
	DIR* dir = opendir(strPath.c_str());
	if (dir != nullptr)
	{
		dirent* entry;
		while ((entry = readdir(dir)) != nullptr) {
			std::string fileName = entry->d_name;
			if (fileName.length() > 3 && fileName.substr(fileName.length() - 3) == strLibExtension) {
				files.push_back(strPath + "/" + fileName);
			}
		}
		closedir(dir);
	}
#endif
	else 
	{
		PRINT_LOG(" failed to find lib in path: " << strPath.c_str());
	}


	//加载动态库
	for (const auto& iterPath : files)
	{
#ifdef OS_WIN
		HINSTANCE hDLL = LoadLibrary(iterPath.c_str());
		if (hDLL == NULL) {
			FreeLibrary(hDLL);
			continue;;
		}

		// 获取接口函数
		getPluginService myFunc = (getPluginService)GetProcAddress(hDLL, "getPlugin");
		if (myFunc == nullptr) {
			FreeLibrary(hDLL);
			continue;;
		}
		auto pPlugin = myFunc();
		m_mapTools[pPlugin->getTypeName()] = pPlugin;

		//FreeLibrary(hDLL);
#elif defined OS_LINUX
		void* handle = dlopen(iterPath.c_str(), RTLD_LAZY);
		if (handle == nullptr)
		{
			dlclose(handle);
			continue;
		}

		// 获取接口函数
		getPluginService myFunc = (getPluginService)dlsym(handle, "getPlugin");
		if (myFunc == nullptr) {
			dlclose(handle);
			continue;
		}
		auto pPlugin = myFunc();
		m_mapTools[pPlugin->getTypeName()] = pPlugin;

		//dlclose(handle);
#endif
	}
	PRINT_LOG(" plugin num is " << m_mapTools.size());
	return m_mapTools.size();
}

MmrTools::IToolBase* MmrTools::CPluginManager::getToolByName(const std::string& strName)
{
	//std::cout << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << strName.c_str() << std::endl;
	auto iterTool = m_mapTools.find(strName);
	if (iterTool != m_mapTools.end())
	{
		return iterTool->second;
	}
	else
	{
		return nullptr;
	}
}

MmrTools::CPluginManager::CPluginManager()
{

}

MmrTools::CPluginManager::~CPluginManager()
{

}

//template<typename _T>
//IToolBase* MmrTools::CPluginManager::getTool()
//{
//	std::string strTypeName = STR(_T);
//	auto iterTool = m_mapTools.find(strTypeName);
//	if (iterTool !=  m_mapTools.end())
//	{
//		return iterTool->second;
//	}
//	else 
//	{
//		return nullptr;
//	}
//}