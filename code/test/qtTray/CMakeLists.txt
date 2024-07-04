#工程名称
project(qtTray)

# 开启Qt MOC
set(CMAKE_AUTOMOC ON)
#开启Qt ROC
set(CMAKE_AUTORCC ON)
# 开启Qt UIC
set(CMAKE_AUTOUIC ON)

#设置Qt库
set(QTCOMPONENT Core Gui Widgets)


# 查找Qt库
find_package(Qt5 REQUIRED ${QTCOMPONENT})

foreach(QtComp ${QTCOMPONENT})
	include_directories(${Qt5${QtComp}_INCLUDE_DIRS})
	set(QT_LIBRARIES ${QT_LIBRARIES} ${Qt5${QtComp}_LIBRARIES})
endforeach()

#message("QT_LIBRARIES ${QT_LIBRARIES}")

file(GLOB FILE_HEADS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
source_group("include" FILES ${FILE_HEADS})

file(GLOB FILE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
source_group("source" FILES ${FILE_SOURCES})

file(GLOB FILE_UI "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")
source_group("ui" FILES ${FILE_UI})

file(GLOB FILE_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc")
source_group("resource" FILES ${FILE_RESOURCE})

# 增加动态链接库
add_executable(${PROJECT_NAME} #WIN32
	${FILE_HEADS}
	${FILE_SOURCES}
	${FILE_UI}
	${FILE_RESOURCE})
	
target_link_libraries(${PROJECT_NAME} 
	${QT_LIBRARIES}
	)
	
INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "bin")