# CMake版本约束
cmake_minimum_required(VERSION 3.0)
#工程名称
project(Mounmory)
#工程放设置到文件夹中
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(THIRD_PART_DIR "" CACHE PATH "set third part depend directory")

if(NOT THIRD_PART_DIR)
	message(FATAL_ERROR "please set THIRD_PART_DIR value!")
endif()

if(WIN32)
	STRING(REPLACE "-O2" "-Od" CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})#取消优化
	if(MSVC)
		if(MSVC_VERSION LESS 1900) # 判断编译器版本是否低于VS2015
			message(FATAL_ERROR "MSVC version must be at least 14.0 (Visual Studio 2015)!")
		endif()
	endif()

	link_directories(${THIRD_PART_DIR}/lib/win64)
	message("platform windows")
else(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")#c++11 do not has make_unique
	set(CMAKE_PREFIX_PATH "/opt/Qt5.12.0/5.12.0/gcc_64/" CACHE PATH "set path for find packet, multiple paths using ';' segmentation")
	set(CMAKE_INSTALL_RPATH ./ ${CMAKE_PREFIX_PATH}/lib)#设置运行依赖库目录
	
	#link_directories(${THIRD_PART_DIR}/lib/linux)#提前安装到系统
	#link_directories(${THIRD_PART_DIR}/bin/linux)
	message("platform linux")
endif()

#包含目录
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)#可执行文件位置
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)#默认存放动态库的位置
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)#默认存放静态库的位置，以及MSVC中动态库的lib文件的位置。

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmakeModules)

include(MacroUtil)
include(MacroBuildSharedLib)
include(MacroBuildToolPlugin)
include(MacroBuildTestApp)
include(MacroBuildComponent)

SET(COMMON_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/common/include)
SET(COMMON_INCLUDE_UTIL_DIR ${CMAKE_SOURCE_DIR}/common/include/util)
SET(COMMON_INCLUDE_LIBNET_DIR ${CMAKE_SOURCE_DIR}/common/include/libnet)

include_directories(${THIRD_PART_DIR}/include)
include_directories(${COMMON_INCLUDE_DIR})
#include_directories(${COMMON_INCLUDE_UTIL_DIR})
#include_directories(${COMMON_INCLUDE_LIBNET_DIR})


#输出可执行文件目录
#SET(TARGET_BIN_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

ADD_SUBDIRECTORY(app)
ADD_SUBDIRECTORY(common)
ADD_SUBDIRECTORY(service)
#ADD_SUBDIRECTORY(tools)

if(WIN32)
	option(BUILD_CREO_LIB "build creo lib" "ON")
	if(BUILD_CREO_LIB)
		ADD_SUBDIRECTORY(creo)
	endif(BUILD_CREO_LIB)
	option(ENABLE_WINDUMP "Windows MiniDumpWriteDump" OFF)
endif(WIN32)

#构建测试用例
option(BUILD_TESTS "build tests" "ON")
if(BUILD_TESTS)
	ADD_SUBDIRECTORY(test)
endif(BUILD_TESTS)