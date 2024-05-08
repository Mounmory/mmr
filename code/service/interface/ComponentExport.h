﻿#ifndef COMPONENTEXPORT_H
#define COMPONENTEXPORT_H

#include "Common_def.h"

#if defined(OS_WIN)
//#pragma execution_character_set("utf-8")
	#ifdef MMR_COMPO_CORE_EXPORT
		#define COMPO_CORE_CLASS_API __declspec(dllexport)
		#define COMPO_CORE_FUN_API extern "C" __declspec(dllexport)
	#else
		#define COMPO_CORE_CLASS_API  __declspec(dllimport)
		#define COMPO_CORE_FUN_API extern "C" __declspec(dllimport)
	#endif

	#ifdef MMR_COMPONENT_EXPORT
	#define COMPONENT_CLASS_API __declspec(dllexport)
	#define COMPONENT_FUN_API extern "C" __declspec(dllexport)
	#else
	#define COMPONENT_CLASS_API  __declspec(dllimport)
	#define COMPONENT_FUN_API extern "C" __declspec(dllimport)
	#endif

#else
	#define COMPO_CORE_CLASS_API 
	#define COMPO_CORE_FUN_API extern "C" 

	#define COMPONENT_CLASS_API 
	#define COMPONENT_FUN_API extern "C" 
#endif

#endif

