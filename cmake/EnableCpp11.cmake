if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	add_compile_options( -std=c++11 -Os -O3 -fexceptions )
endif()

if (MINGW)
  add_compile_options( -std=c++11 -Os -O3 -fexceptions )
endif()