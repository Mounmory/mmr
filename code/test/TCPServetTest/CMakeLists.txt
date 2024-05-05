#工程名称
project(TCPServetTest)

include_directories(${COMMON_INCLUDE_LIBNET_DIR}/base)
include_directories(${COMMON_INCLUDE_LIBNET_DIR}/cppnet)
include_directories(${COMMON_INCLUDE_LIBNET_DIR}/cpputil)
include_directories(${COMMON_INCLUDE_LIBNET_DIR}/event)
include_directories(${COMMON_INCLUDE_LIBNET_DIR}/http)
include_directories(${COMMON_INCLUDE_LIBNET_DIR}/util)
include_directories(${COMMON_INCLUDE_LIBNET_DIR}/hv)

build_test_app(TCPServetTest
	TARGET_LIBRARIES mmrNet
	)
