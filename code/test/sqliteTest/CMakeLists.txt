#工程名称
project(sqliteTest)

build_test_app(${PROJECT_NAME}
	TARGET_LIBRARIES mmrUtil sqlite3
	)
