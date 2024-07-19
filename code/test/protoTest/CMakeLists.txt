#工程名称
project(protoTest)

build_test_app(protoTest
	TARGET_LIBRARIES mmrUtil libprotobuf libprotoc libprotobuf-lite
	)
