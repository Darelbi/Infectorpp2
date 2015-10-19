#******************************************************************************
# Copyright (C) 2015 Oliveri Dario
# See copyright notice in LICENSE.md file.
#******************************************************************************


#==============================================================================
# Welcome to Infectorpp Build system.
#==============================================================================

cmake_minimum_required( VERSION 2.8)
project( Infectorpp2)

# -DCMAKE_BUILD_TYPE:STRING=Release
# Debug, MinSizeRel, RelWithDebugInfo, Release, General

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR
  "Cannot write to source folder, please run CMake from another dir")
  message(FATAL_ERROR
  "try console commands (separed by @): mkdir build @ cd build @ cmake-gui ..")
endif()

#==============================================================================
# Use the following options to customize the build
#==============================================================================

set( INFECTORPP2_TARGET_NAME "bin" CACHE STRING
    "Give the name you like most to a logical target")


set( INFECTORPP2_UNITY_BUILD true CACHE BOOL
	"choose TRUE if you are compiling Infectorpp2 just once, FALSE otherwise")
	
	
set( INFECTORPP2_ENABLE_PROFILING false CACHE BOOL
	"choose TRUE if you want to compile using the native profiler")
	
	
set( INFECTORPP2_ENABLE_TESTS true CACHE BOOL
	"choose TRUE if you want to compile also tests")
	
	
set( INFECTORPP2_ENABLE_EXCEPTIONS true CACHE BOOL
	"choose TRUE if you want to get exceptions instead of application crash")


#==============================================================================
# Enable C++11 support ( MIT LICENSE: Copyright (c) 2013 Nathan Osman)
#==============================================================================

# code has minor tweaks
if((MSVC AND (MSVC12 OR MSVC14)) OR
   (CMAKE_COMPILER_IS_GNUCXX
		AND NOT ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 4.6) OR
   (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"
		AND NOT ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 3.1))

	message(STATUS "Checking for C++11 compiler - available")
else()
	message(FATAL_ERROR "Checking for C++11 compiler - unavailable")
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	
	#Profile code with GCC (uncomment to enable gprof profiling)
	if(CMAKE_COMPILER_IS_GNUCXX AND INFECTORPP2_ENABLE_PROFILING)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
		SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
		SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
	endif()
	
endif()

if(NOT ${INFECTORPP2_ENABLE_EXCEPTIONS})
	add_definitions(-DINFECTORPP_DISABLE_EXCEPTION_HANDLING=1)
endif()

#==============================================================================
# Add source files to static library
#==============================================================================


file( GLOB INFECTORPP2_SOURCE_FILES
							"include/Infectorpp/priv/*.cpp")

file( GLOB INFECTORPP2_HEADER_FILES
							"include/Infectorpp/*.hpp"
							"include/Infectorpp/priv/*.hpp")

set_source_files_properties( 	${INFECTORPP2_HEADER_FILES}
									PROPERTIES HEADER_FILE_ONLY true)


# keep unity build file updated even when not using unity build.?
# It can be handy, but paths are machine specific so require cmake anyway.
file( WRITE include/Infectorpp/priv/all.cxx "// Auto-generated build file\n")

foreach( source_file ${INFECTORPP2_SOURCE_FILES} )

	file( APPEND include/Infectorpp/priv/all.cxx "#include \"${source_file}\"\n")

endforeach(source_file)


if( INFECTORPP2_UNITY_BUILD)

	# Do not build source files...
	set_source_files_properties( 	${INFECTORPP2_SOURCE_FILES}
									PROPERTIES HEADER_FILE_ONLY true)

	add_library( libInfectorpp2 STATIC
										include/Infectorpp/priv/all.cxx
										${INFECTORPP2_SOURCE_FILES}
										${INFECTORPP2_HEADER_FILES})

else()

	add_library( libInfectorpp2 STATIC
										${INFECTORPP2_SOURCE_FILES}
										${INFECTORPP2_HEADER_FILES})

endif()



set_target_properties( libInfectorpp2  PROPERTIES
										PREFIX "static_"   )


#==============================================================================
# Copy static library to "bin folder"
#==============================================================================

add_custom_command(TARGET libInfectorpp2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:libInfectorpp2>
    "../../bin/${INFECTORPP2_TARGET_NAME}/$<TARGET_FILE_NAME:libInfectorpp2>"
)


#==============================================================================
# Preparation for Unit testing.
#==============================================================================

if(NOT ${INFECTORPP2_ENABLE_TESTS})
	return()
endif()



enable_testing()
add_library( libCatch STATIC "tests/catch.cxx")
add_custom_target(build_and_test ${CMAKE_CTEST_COMMAND} -V)

function(create_test parm) #tests helper function

	get_filename_component( ExeName		${parm} NAME_WE)
	get_filename_component( SourceFile	${parm} ABSOLUTE)

	add_executable( ${ExeName} ${SourceFile})

	# ARGN is list of arguments past "parm". So all libraries that we link
	target_link_libraries( ${ExeName} ${ARGN})


	add_dependencies( build_and_test ${ExeName})

	target_include_directories( ${ExeName} PUBLIC "include/Infectorpp")

	add_test( ${ExeName} ${ExeName})

	add_custom_command(TARGET ${ExeName}
					   POST_BUILD
					   COMMAND ${ExeName}
					   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
					   COMMENT "Running ${ExeName}" VERBATIM)
endfunction(create_test)


#==============================================================================
# Unit testing and compile demos
#==============================================================================


file( GLOB INFECTORPP_COMMON_TEST_FILES	"tests/*.cpp")
foreach( source_file ${INFECTORPP_COMMON_TEST_FILES} )
	create_test( ${source_file} libCatch libInfectorpp2)
endforeach(source_file)
