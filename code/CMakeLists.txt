# CMake版本约束
cmake_minimum_required(VERSION 3.0)
#工程名称
project(Mounmory)
#工程放设置到文件夹中
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(WIN32)
STRING(REPLACE "-O2" "-Od" CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})#取消优化
message("platform windows")
else(UNIX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_PREFIX_PATH "/opt/Qt5.12.0/5.12.0/gcc_64/" CACHE PATH "set Qt GCC path")
set(CMAKE_INSTALL_RPATH ./ ${CMAKE_PREFIX_PATH}/lib)#设置运行依赖库目录
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

#输出可执行文件目录
#SET(TARGET_BIN_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

ADD_SUBDIRECTORY(common)
ADD_SUBDIRECTORY(tools)

if(WIN32)
	option(BUILD_CREO_LIB "build creo lib" "ON")
	if(BUILD_CREO_LIB)
		ADD_SUBDIRECTORY(creo)
	endif(BUILD_CREO_LIB)
endif(WIN32)

#构建测试用例
option(BUILD_TESTS "build tests" "ON")
if(BUILD_TESTS)
	ADD_SUBDIRECTORY(test)
endif(BUILD_TESTS)