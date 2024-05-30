#ifndef CLOGGERCTRL_H
#define CLOGGERCTRL_H
#include <memory>
#include <unordered_map>
#include "ComponentExport.h"
#include "util/Clogger.h"

/*
	组件日志等级控制类
	保存各个组件日志实例指针，动态修改实例中的日志等级
*/
BEGINE_NAMESPACE(mmrComp)

class COMPO_CORE_CLASS_API CLoggerCtrl
{
	using MapLogCtrl = std::unordered_map<std::string, std::weak_ptr<mmrUtil::LogWrapper>>;
public:
	CLoggerCtrl();
	~CLoggerCtrl();

	MapLogCtrl& getMapCtrollerPtr() { return m_mapCompLogger; }

	void loop();
private:
	MapLogCtrl m_mapCompLogger;//所有控件日志组件
};

END_NAMESPACE(mmrComp)

#endif