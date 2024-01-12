include_directories(${CMAKE_SOURCE_DIR}/common/include)
include_directories(${CMAKE_SOURCE_DIR}/tools/include)
include_directories(${CMAKE_SOURCE_DIR}/tools/include/plugins)

SUBDIRLIST(SRC_DIR_LIST ${CMAKE_CURRENT_SOURCE_DIR})

# 查找所有子文件夹和文件夹
foreach(subdirectory ${SRC_DIR_LIST})
	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${subdirectory}/CMakeLists.txt")
		add_subdirectory(${subdirectory})
		if(TARGET ${subdirectory})
		 SET_PROPERTY(TARGET ${subdirectory} PROPERTY FOLDER "tools/plugins")
		 #message("target subdirectory: ${subdirectory}")
		endif(TARGET ${subdirectory})
	endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${subdirectory}/CMakeLists.txt")
endforeach()

# 查找所有子文件夹和文件夹
# 过滤出子文件夹
# 块注释
#[[
file(GLOB subdirectories RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
foreach(subdirectory ${subdirectories})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${subdirectory})
        list(APPEND subdirectories_list ${subdirectory})
		if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${subdirectory}/CMakeLists.txt")
			add_subdirectory(${subdirectory})
			if(TARGET ${subdirectory})
			 SET_PROPERTY(TARGET ${subdirectory} PROPERTY FOLDER "tools/plugins")
			 #message("target subdirectory: ${subdirectory}")
			endif(TARGET ${subdirectory})
		endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${subdirectory}/CMakeLists.txt")
    endif()
endforeach()
]]