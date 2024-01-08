#ifndef CPLUGINMANAGER_H
#define CPLUGINMANAGER_H
#include "Common.h"
#include "CoreCommon.h"
#include <typeinfo>
#include <map>

BEGINE_NAMESPACE(MmrTools)

class IToolBase;

class TOOLCORE_CLASS_API CPluginManager
{
private:
	CPluginManager();
	~CPluginManager();

public:
	static CPluginManager* getPluginManager();

	//插件路径
	//返回插件数量
	int loadPuglins(const std::string& strPath);

	template<typename _T>
	_T* getTool()
	{
		const std::type_info& type = typeid(_T);
		return dynamic_cast<_T*>(getToolByName(type.name()));
	}


private:
	IToolBase* getToolByName(const std::string& strName);

private:
	std::map<std::string, IToolBase*> m_mapTools;
};

END_NAMESPACE(MmrTools)
#endif // !CPLUGINMANAGER_H
