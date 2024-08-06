#工程名称
project(protoRpcClient)

#设置protobuf源文件
add_definitions(-DPROTOBUF_USE_DLLS)

include_directories(${COMMON_INCLUDE_LIBNET_DIR}/cpputil)

include_directories(${COMMON_INCLUDE_LIBNET_DIR}/hv)

include_directories(${COMMON_INCLUDE_LIBNET_DIR}/cppnet)

include_directories(${PROTO_GENERATE_FILE_PATH}/protoRPCTest)

file(GLOB PROTO_HEADS "${PROTO_GENERATE_FILE_PATH}/protoRPCTest/*.h")
	source_group("include/proto" FILES ${PROTO_HEADS})
	
file(GLOB PROTO_SRC "${PROTO_GENERATE_FILE_PATH}/protoRPCTest/*.cc")
	source_group("source/proto" FILES ${PROTO_SRC})

if(WIN32)
set(LINK_LIBS mmrNet mmrUtil libprotobuf)
else(WIN32)
set(LINK_LIBS mmrNet mmrUtil protobuf)
endif(WIN32)

build_test_app(${PROJECT_NAME}
	TARGET_SRC_FILES ${PROTO_HEADS} ${PROTO_SRC}
	TARGET_LIBRARIES ${LINK_LIBS}
	)