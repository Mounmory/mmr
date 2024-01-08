#ifndef PLUGININTERFACECOMMON_H
#define PLUGININTERFACECOMMON_H

#if defined(_MSC_VER)
//#pragma execution_character_set("utf-8")
#ifdef MMR_TOOLPLUGIN_EXPORT
#define PLUGIN_CLASS_API __declspec(dllexport)
#define PLUGIN_FUN_API extern "C" __declspec(dllexport)
#else
#define PLUGIN_CLASS_API  __declspec(dllimport)
#define PLUGIN_FUN_API extern "C" __declspec(dllimport)
#endif
#else
#define PLUGIN_CLASS_API 
#define PLUGIN_FUN_API extern "C" 
#endif

#endif // !PLUGININTERFACECOMMON_H
