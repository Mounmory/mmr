#工程名称
if(WIN32)
project(lockFreeDataTest)

build_test_app(lockFreeDataTest
	TARGET_LIBRARIES mmrUtil
	)
endif()