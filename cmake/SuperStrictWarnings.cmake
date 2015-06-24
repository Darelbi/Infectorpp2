if ($ENV{CMAKE_FORCE_OPTIONS_FOR} MATCHES "Clang")
	add_compile_options( -Woverloaded-virtual -Wctor-dtor-privacy -Wconversion
                      -Wformat=2 -Winit-self -Winline -Wmissing-include-dirs
                      -Wredundant-decls -Wshadow -Wstack-protector
                      -Wstrict-null-sentinel -Wswitch-default -Winvalid-pch
                      -Wstrict-aliasing=2 -Wunknown-pragmas -Wundef
                      -Wpointer-arith -Wcast-qual -Wwrite-strings
                      -Wvolatile-register-var -Wno-unused-parameter
                      -Wno-variadic-macros -Wunreachable-code -Wcast-align
                      #-Wzero-as-null-pointer-constant #commented because Cmake generate crappy code 
					  -Wold-style-cast)
endif()

if ($ENV{CMAKE_FORCE_OPTIONS_FOR} MATCHES "GCC")
  add_compile_options( -Woverloaded-virtual -Wctor-dtor-privacy -Wconversion
                      -Wformat=2 -Winit-self -Winline -Wmissing-include-dirs
                      -Wredundant-decls -Wshadow -Wstack-protector
                      -Wstrict-null-sentinel -Wswitch-default -Winvalid-pch
                      -Wstrict-aliasing=2 -Wunknown-pragmas -Wundef
                      -Wpointer-arith -Wcast-qual -Wwrite-strings
                      -Wvolatile-register-var -Wno-unused-parameter
                      -Wno-variadic-macros -Wunreachable-code -Wcast-align
                      #-Wzero-as-null-pointer-constant #commented because Cmake generate crappy code 
					  -Wold-style-cast)
endif()