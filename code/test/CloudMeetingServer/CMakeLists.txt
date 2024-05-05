#工程名称
if(UNIX)
project(CloudMeetingServer)
	
build_test_app(CloudMeetingServer
	TARGET_LIBRARIES pthread
	)
endif()

