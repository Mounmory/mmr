#工程名称
project(sqliteTest)

build_test_app(sqliteTest
	TARGET_LIBRARIES mmrUtil sqlite3
	)
