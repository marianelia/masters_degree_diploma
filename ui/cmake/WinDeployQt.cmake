#
# CMake wrapper to call windeployqt in Windows
#
# The files are placed in windeployqt folder in the toplevel
# build directory

set(HAVE_WINDEPLOY True)

function(WinDeployQt)
	cmake_parse_arguments(_deploy
		"FORCE;COPYDLLS"
		"TARGET"
		"INCLUDE_MODULES;EXCLUDE_MODULES"
		${ARGN}
		)

	if(NOT _deploy_TARGET)
		message(FATAL_ERROR "A TARGET must be specified")
	endif()

	get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
	if(isMultiConfig)
		list(APPEND _ARGS $<$<CONFIG:Debug>:--debug>$<$<CONFIG:Release>:--release-with-debug-info>$<$<CONFIG:RelWithDebInfo>:--release>)
	else()
		if(CMAKE_BUILD_TYPE STREQUAL "Debug")
			list(APPEND _ARGS --debug)
		elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
			list(APPEND _ARGS --release-with-debug-info)
		elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
			list(APPEND _ARGS --release)
		endif()
	endif()
	
	if(_deploy_FORCE)
		list(APPEND _ARGS --force)
	endif()
	
	
	foreach(mod ${_deploy_INCLUDE_MODULES})
		string(TOLOWER ${mod} mod)
		string(REPLACE "qt5::" "" mod ${mod})
		list(APPEND _ARGS "--${mod}")
	endforeach()
	foreach(mod ${_deploy_EXCLUDE_MODULES})
		string(TOLOWER ${mod} mod)
		string(REPLACE "qt5::" "" mod ${mod})
		list(APPEND _ARGS "--no-${mod}")
	endforeach()

	
	get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(_deploy_PROGRAM ${QT5_QMAKE_EXECUTABLE} PATH)
    set(_deploy_PROGRAM "${_deploy_PROGRAM}/windeployqt.exe")

		
	add_custom_command(TARGET ${_deploy_TARGET} POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E env 
		${_deploy_PROGRAM} $<TARGET_FILE:${_deploy_TARGET}>
		COMMENT "Executing WinDeployQt for ${module_name}..")
	
endfunction()

