if ( MSVC)

else()

	SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -Woverloaded-virtual -Wctor-dtor-privacy -Wconversion -Wformat=2 -Winit-self -Winline     -Wmissing-include-dirs-Wredundant-decls -Wshadow -Wstack-protector -Wstrict-null-sentinel -Wswitch-default -Winvalid-pch -Wstrict-aliasing=2 -Wunknown-pragmas -Wundef -Wpointer-arith -Wcast-qual -Wwrite-strings -Wvolatile-register-var -Wno-unused-parameter -Wno-variadic-macros -Wunreachable-code -Wcast-align -Wold-style-cast")
	
endif()