#=============================================================================
# Welcome to Infectorpp2 Build system. ./tests
#=============================================================================
cmake_minimum_required( VERSION 2.8)
project( infectorppTests)


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


#-----------------------------------CONFIGURE---------------------------------
#-----------------------------------------------------------------------------

include( GenerateTestDriver)

include_directories("../include/Infectorpp/")

generate_test_driver( tests)
target_link_libraries( tests libInfectorpp2)
