#
# Depends on:
#  cmake_parse_arguments ( >= CMake 2.8.3)
#

MACRO(build_shared_library targetName)
	cmake_parse_arguments(
	MMR
    "" # no options
    "FOLDER" # one value args
    "SRCS;MOC_SRCS;UI_FORMS;SRC_FILES;TARGET_LIBRARIES;TARGET_WIN_LIBS;TARGET_LINUX_LIBS;RESOURCES" # multi value args
    ${ARGN}
    )
	
	message("build_shared_library ${targetName}")
	
	# ���Ӷ�̬���ӿ�
	add_library(${targetName} SHARED ${MMR_SRC_FILES})
		
	#target_compile_definitions(${targetName} PRIVATE EXPORT_LIBRARY)#ͬʱ���ɾ�̬��

	#conmmon target link libs 
	if(MMR_TARGET_LIBRARIES)
		target_link_libraries(${PROJECT_NAME} ${MMR_TARGET_LIBRARIES})
	endif()
	
	#windows only target link libs
	if(WIN32 AND MMR_TARGET_WIN_LIBS)
		target_link_libraries(${PROJECT_NAME} ${MMR_TARGET_WIN_LIBS})
	endif()

	#linux only target link libs
	if(UNIX AND MMR_TARGET_LINUX_LIBS)
		target_link_libraries(${PROJECT_NAME} ${MMR_TARGET_LINUX_LIBS})
	endif()
	
	#set project folder
	if(MMR_FOLDER)
		SET_PROPERTY(TARGET ${targetName} PROPERTY FOLDER ${MMR_FOLDER})
	endif()

	#ʹ��UTF8����
	#add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

#set build folders
#[[
	foreach(conf DEBUG MINSIZEREL RELWITHDEBINFO RELEASE)
		if(WIN32)
		set_target_properties(${targetName}  PROPERTIES
	  		RUNTIME_OUTPUT_DIRECTORY_${conf} ${CMAKE_BINARY_DIR}/bin
			LIBRARY_OUTPUT_DIRECTORY_${conf} ${CMAKE_BINARY_DIR}/bin
			)
		else(UNIX)
			set_target_properties(${targetName} PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY_${conf} ${CMAKE_BINARY_DIR}/bin
			LIBRARY_OUTPUT_DIRECTORY_${conf} ${CMAKE_BINARY_DIR}/bin)
		endif()
	endforeach()
]]
	#install libs
	install(TARGETS ${targetName} 
		RUNTIME DESTINATION bin #window��dll�ļ�
		LIBRARY DESTINATION bin #linux��.so�ļ�
		ARCHIVE DESTINATION lib)#��̬��
ENDMACRO()