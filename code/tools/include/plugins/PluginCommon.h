#ifndef PLUGINCOMMON_H
#define PLUGINCOMMON_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
	//#pragma execution_character_set("utf-8")
	#ifdef MMR_TOOLPLUGIN_EXPORT
		#define PLUGIN_FUN_API extern "C" __declspec(dllexport)
	#else
		#define PLUGIN_FUN_API extern "C" __declspec(dllimport)
	#endif
#else
	#define PLUGIN_FUN_API extern "C" 
#endif

/* register interface by interface class */
#define PLUGIN_INTERFACE_NAME(inter)\
public:\
	virtual const std::string getTypeName()const override\
	{\
		static const std::type_info& type = typeid(inter);\
		return type.name();\
	}

/* get plugin function from dll interface */
#define PLUGIN_REGISTER_FUNC(ins)\
PLUGIN_FUN_API MmrTools::IToolBase* getPlugin()\
{\
	static ins* plugin = new ins;\
	return plugin;\
}

#endif // !PLUGININTERFACECOMMON_H
