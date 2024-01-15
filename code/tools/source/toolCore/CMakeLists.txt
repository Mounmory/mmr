project(toolCore)

include_directories(${CMAKE_SOURCE_DIR}/common/include)
include_directories(${CMAKE_SOURCE_DIR}/tools/include)
include_directories(${CMAKE_SOURCE_DIR}/tools/include/toolCore)

#文件分组
file(GLOB TOOLCOMMON_HEADS 
	"${CMAKE_SOURCE_DIR}/common/include/*.h"
	"${CMAKE_SOURCE_DIR}/tools/include/*.h"
	"${CMAKE_SOURCE_DIR}/tools/include/*.hpp")
	
source_group("common" FILES ${TOOLCOMMON_HEADS})

file(GLOB TOOLCORE_HEADS 
	"${CMAKE_SOURCE_DIR}/tools/include/toolCore/*.h")
source_group("include" FILES ${TOOLCORE_HEADS})

file(GLOB TOOLCORE_SOURCE 
	"${CMAKE_SOURCE_DIR}/tools/source/toolCore/*.cpp")
source_group("source" FILES ${TOOLCORE_SOURCE})

add_definitions(-DMMR_TOOLCORE_EXPORT)

build_shared_library( toolCore
	#project folder in VS
	FOLDER tools
	#源文件
	SRC_FILES ${TOOLCOMMON_HEADS} ${TOOLCORE_HEADS} ${TOOLCORE_SOURCE}
	#linux 环境下依赖库
	TARGET_LINUX_LIBS dl
	)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/tools/include/interface
    DESTINATION include/tools)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/tools/include/toolCore
    DESTINATION include/tools)