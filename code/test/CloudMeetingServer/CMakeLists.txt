#工程名称
if(UNIX)
project(CloudMeetingServer)
	
build_test_app(${PROJECT_NAME}
	TARGET_LIBRARIES pthread
	)
endif()

