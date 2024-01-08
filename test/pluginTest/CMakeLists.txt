#工程名称
project(pluginTest)

include_directories(${CMAKE_SOURCE_DIR}/common/include)

include_directories(${CMAKE_SOURCE_DIR}/tools/include)

file(GLOB COMMON_HEADS "${CMAKE_SOURCE_DIR}/common/include/*.h")
source_group("include" FILES ${COMMON_HEADS})

file(GLOB FILE_HEADS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
source_group("include" FILES ${FILE_HEADS})

file(GLOB FILE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
source_group("source" FILES ${FILE_SOURCES})	


# 增加动态链接库
add_executable(${PROJECT_NAME} #WIN32
	${COMMON_HEADS}
	${FILE_HEADS}
	${FILE_SOURCES})
	
target_link_libraries(${PROJECT_NAME} 
	mmrCommon
	toolCore
	)

INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "bin")