#ifndef TOOLCOMMON_H
#define TOOLCOMMON_H

#if defined(_MSC_VER)
//#pragma execution_character_set("utf-8")
#ifdef MMR_TOOLCORE_EXPORT
#define TOOLCORE_CLASS_API __declspec(dllexport)
#define TOOLCORE_FUN_API extern "C" __declspec(dllexport)
#else
#define TOOLCORE_CLASS_API  __declspec(dllimport)
#define TOOLCORE_FUN_API extern "C" __declspec(dllimport)
#endif
#else
#define TOOLCORE_CLASS_API 
#define TOOLCORE_FUN_API extern "C" 
#endif

#endif

