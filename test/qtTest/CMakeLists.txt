#工程名称
project(qtTest)

# 开启Qt MOC
set(CMAKE_AUTOMOC ON)
#开启Qt ROC
set(CMAKE_AUTORCC ON)
# 开启Qt UIC
set(CMAKE_AUTOUIC ON)
#set(QT Core Gui Widgets Charts)
set(QT Core Gui Widgets)
# 查找Qt库
find_package(Qt5 REQUIRED ${QT})

include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Charts_INCLUDE_DIRS})
		
set(QT_LIBRARIES ${Qt5Widgets_LIBRARIES} ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Charts_LIBRARIES})

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
	)
	
INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "bin")