#工程名称
project(serviceApp)
	
build_test_app(serviceApp
	TARGET_LIBRARIES mmrUtil serviceFramework mmrNet
	)
	
INSTALL(FILES ${THIRD_PART_DIR}/config/serviceApp.json
	DESTINATION bin/config)