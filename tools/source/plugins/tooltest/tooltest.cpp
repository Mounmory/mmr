#include "tooltest/tooltest.h"
#include "interface/PluginInterfaceCommon.h"
#include <iostream>


MmrTools::tooltest::tooltest()
{

}

MmrTools::tooltest::~tooltest()
{

}

const std::string MmrTools::tooltest::getTypeName() const
{
	static const std::type_info& type = typeid(MmrTools::IToolTest);
	return type.name();
}

void MmrTools::tooltest::testHello()
{
	PRINT_LOG(" test hello load successfully!" );
}

PLUGIN_FUN_API MmrTools::IToolBase* getPlugin()
{
	static MmrTools::tooltest* plugin = new MmrTools::tooltest;
	return plugin;
}