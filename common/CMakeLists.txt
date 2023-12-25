project(mmr_Common)

#包含头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#文件分组
file(GLOB FILE_HEADS "${CMAKE_CURRENT_SOURCE_DIR}/include/util/*.h")
source_group("include/util" FILES ${FILE_HEADS})

file(GLOB FILE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/source/util/*.cpp")
source_group("source/util" FILES ${FILE_SOURCES})	

add_definitions(-DMMR_COMMON_EXPORT)

#STRING(REPLACE "/O2" "/Od" CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})

# 增加动态链接库
add_library(${PROJECT_NAME} SHARED
	${FILE_HEADS}
	${FILE_SOURCES})
	
target_compile_definitions(${PROJECT_NAME} PRIVATE EXPORT_LIBRARY)#同时生成动态库

SET_PROPERTY(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Common")
#使用UTF8编译
#add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

INSTALL(TARGETS ${PROJECT_NAME} 
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib)