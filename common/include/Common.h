#ifndef COMMON_H
#define COMMON_H

#if defined(_MSC_VER)

	//#pragma execution_character_set("utf-8")

	#ifdef MMR_COMMON_EXPORT
	#define COMMON_API __declspec(dllexport)
	#else
	#define COMMON_API __declspec(dllimport)
	#endif
#else
	#define COMMON_API
#endif



#endif