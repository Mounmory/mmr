project(tooltest)

#文件分组
file(GLOB TOOLCOMMON_HEADS 
	"${CMAKE_SOURCE_DIR}/common/include/*.h")
source_group("common" FILES ${TOOLCOMMON_HEADS})

file(GLOB TOOLINTERFACE_HEADS 
	"${CMAKE_SOURCE_DIR}/tools/include/interface/*.hpp"
	"${CMAKE_SOURCE_DIR}/tools/include/interface/*.h")
source_group("interface" FILES ${TOOLINTERFACE_HEADS})

file(GLOB TOOLSTEST_HEADS "${CMAKE_SOURCE_DIR}/tools/include/plugins/tooltest/*.h")
source_group("include" FILES ${TOOLSTEST_HEADS})

message("TOOLSTEST_HEADS: ${TOOLSTEST_HEADS}")

file(GLOB TOOLSTEST_SOURCE 
	"${CMAKE_SOURCE_DIR}/tools/source/plugins/tooltest/*.cpp")
source_group("source" FILES ${TOOLSTEST_SOURCE})

message("TOOLSTEST_SOURCE: ${TOOLSTEST_SOURCE}")

add_definitions(-DMMR_TOOLPLUGIN_EXPORT)

# 增加动态链接库
add_library(${PROJECT_NAME} SHARED
	${TOOLCOMMON_HEADS}
	${TOOLINTERFACE_HEADS}
	${TOOLSTEST_HEADS}
	${TOOLSTEST_SOURCE})
	
target_compile_definitions(${PROJECT_NAME} PRIVATE EXPORT_LIBRARY)#同时生成静态库

#使用UTF8编译
#add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

install(TARGETS ${PROJECT_NAME} 
	RUNTIME DESTINATION bin #window下dll文件
	LIBRARY DESTINATION bin #linux下.so文件
	ARCHIVE DESTINATION lib)#静态库
	
#install(DIRECTORY ${CMAKE_SOURCE_DIR}/tools/include
#    DESTINATION header/tools)