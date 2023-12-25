# CMake版本约束
cmake_minimum_required(VERSION 2.8)
#工程名称
project(Mounmory)
#工程放设置到文件夹中
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(WIN32)
#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)#同时生成动态库和静态库
else(UNIX)

endif()

#包含目录
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#输出可执行文件目录
SET(TARGET_BIN_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

ADD_SUBDIRECTORY(common)


option(BUILD_CREO_LIB "build creo lib" "ON")
if(BUILD_CREO_LIB)
	ADD_SUBDIRECTORY(creo)
endif(BUILD_CREO_LIB)

#构建测试用例
option(BUILD_TESTS "build tests" "ON")
if(BUILD_TESTS)
	ADD_SUBDIRECTORY(test)
endif(BUILD_TESTS)