if ($ENV{CMAKE_FORCE_OPTIONS_FOR} MATCHES Clang)
	add_compile_options( -std=c++11 -Os -O3 -fexceptions )
endif()

if ($ENV{CMAKE_FORCE_OPTIONS_FOR} MATCHES GCC)
  add_compile_options( -std=c++11 -Os -O3 -fexceptions )
endif()