if(WIN32)
#工程名称
project(qtQualityMng)

# 开启Qt MOC
set(CMAKE_AUTOMOC ON)
#开启Qt ROC
set(CMAKE_AUTORCC ON)
# 开启Qt UIC
set(CMAKE_AUTOUIC ON)

#设置Qt库
if(WIN32)
set(QT Core Gui Widgets AxContainer AxServer AxBase)
else(UNIX)
set(QT Core Gui Widgets)
endif()

# 查找Qt库
find_package(Qt5 REQUIRED ${QT})

#include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS}
 #       ${Qt5Widgets_INCLUDE_DIRS} ${Qt5AxContainer_INCLUDE_DIRS} ${Qt5AxServer_INCLUDE_DIRS} ${Qt5ActiveQt_INCLUDE_DIRS})
		
include_directories(${Qt5Core_INCLUDE_DIRS})
		
set(QT_LIBRARIES ${Qt5Widgets_LIBRARIES} ${Qt5Core_LIBRARIES} 
		${Qt5Gui_LIBRARIES} ${Qt5AxContainer_LIBRARIES} ${Qt5AxServer_LIBRARIES} ${Qt5ActiveQt_LIBRARIES} ${Qt5AxBase_LIBRARIES})

message("QT_LIBRARIES ${QT_LIBRARIES}")

include_directories(${CMAKE_SOURCE_DIR}/common/include)
file(GLOB COMMON_HEADS "${CMAKE_SOURCE_DIR}/common/include/*.h")
source_group("include" FILES ${COMMON_HEADS})

file(GLOB FILE_HEADS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
source_group("include" FILES ${FILE_HEADS})

file(GLOB FILE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
source_group("source" FILES ${FILE_SOURCES})	


# 增加动态链接库
add_executable(${PROJECT_NAME} #WIN32
	${COMMON_HEADS}
	${FILE_HEADS}
	${FILE_SOURCES})
	
target_link_libraries(${PROJECT_NAME} 
	${QT_LIBRARIES}
	mmrUtil
	)
	
INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "bin")
endif()