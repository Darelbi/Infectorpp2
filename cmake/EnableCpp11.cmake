if ( MSVC)

else()

	SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -Os -O3 -fexceptions" )
	
endif()
