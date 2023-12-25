#工程名称
project(strTest)

file(GLOB FILE_HEADS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
source_group("include" FILES ${FILE_HEADS})

file(GLOB FILE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
source_group("source" FILES ${FILE_SOURCES})	


# 增加动态链接库
add_executable(${PROJECT_NAME} 
	${FILE_HEADS}
	${FILE_SOURCES})
	
target_link_libraries(${PROJECT_NAME} 
	mmr_Common
	)

INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)