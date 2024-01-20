project(mmrCommon)

#包含头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#文件分组
file(GLOB COMMON_HEADS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
source_group("include" FILES ${COMMON_HEADS})

file(GLOB COMMON_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
source_group("include" FILES ${COMMON_SOURCE})

file(GLOB FILE_HEADS "${CMAKE_CURRENT_SOURCE_DIR}/include/util/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/util/*.hpp")
source_group("include/util" FILES ${FILE_HEADS})

file(GLOB FILE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/source/util/*.cpp")
source_group("source/util" FILES ${FILE_SOURCES})	

add_definitions(-DMMR_COMMON_EXPORT)

build_shared_library( mmrCommon
	#project folder in VS
	FOLDER Common
	#源文件
	SRC_FILES ${COMMON_HEADS} ${COMMON_SOURCE} ${FILE_HEADS} ${FILE_SOURCES}
	TARGET_LINUX_LIBS pthread #threadPool in linux OS link library
	)
	
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
	DESTINATION include/common)