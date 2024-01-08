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

message("TOOLCOMMON_HEADS: ${TOOLCOMMON_HEADS}")

file(GLOB TOOLCORE_HEADS 
	"${CMAKE_SOURCE_DIR}/tools/include/toolCore/*.h")
source_group("include" FILES ${TOOLCORE_HEADS})

message("TOOLCORE_HEADS: ${TOOLCORE_HEADS}")

file(GLOB TOOLCORE_SOURCE 
	"${CMAKE_SOURCE_DIR}/tools/source/toolCore/*.cpp")
source_group("source" FILES ${TOOLCORE_SOURCE})

message("TOOLCORE_SOURCE: ${TOOLCORE_SOURCE}")

add_definitions(-DMMR_TOOLCORE_EXPORT)

# 增加动态链接库
add_library(${PROJECT_NAME} SHARED
	${TOOLCOMMON_HEADS}
	${TOOLCORE_HEADS}
	${TOOLCORE_SOURCE})
		
target_compile_definitions(${PROJECT_NAME} PRIVATE EXPORT_LIBRARY)#同时生成静态库

if(WIN32)

else(UNIX)#linux下要链接的库
	target_link_libraries(${PROJECT_NAME} 
		dl
		)
endif()


SET_PROPERTY(TARGET ${PROJECT_NAME} PROPERTY FOLDER "tools")

#使用UTF8编译
#add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

install(TARGETS ${PROJECT_NAME} 
	RUNTIME DESTINATION bin #window下dll文件
	LIBRARY DESTINATION bin #linux下.so文件
	ARCHIVE DESTINATION lib)#静态库
	
install(DIRECTORY ${CMAKE_SOURCE_DIR}/tools/include/interface
    DESTINATION header/tools)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/tools/include/toolCore
    DESTINATION header/tools)