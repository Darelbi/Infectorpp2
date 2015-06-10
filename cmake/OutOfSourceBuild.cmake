# OUT OF SOURCE BUILD - SUGGESTED AND REQUIRED ;)
#-----------------------------------------------------------------------------
# Instead of polluting your badeSource directory with all Cmake meta files
# we generate those files inside the "compile/target" directory.
#-----------------------------------------------------------------------------
# to prevent accidental in-source build, we check if output directory
# is the same of input directory. (Idea copied from libSDL2 build system)
#-----------------------------------------------------------------------------
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR}) 
  message(FATAL_ERROR 
  "Cannot write to badeSource folder, please run CMake from another dir")
endif()