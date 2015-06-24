#=============================================================================
# Welcome to BadeEngine3D Build system. ./tests
#=============================================================================
cmake_minimum_required( VERSION 2.8)
project( infectorppTestsDLL)

#-----------------------------------CONFIGURE---------------------------------
#-----------------------------------------------------------------------------
# we test DLLs to because I noticed it now always act the same

include( EnableCpp11)
include( GenerateTestDriver)
add_definitions(-DINFECTOR_IMPORT)

include_directories("../include/Infectorpp/")

generate_test_driver( testsDLL)
set( ENV{PATH} "$ENV{PATH};${CMAKE_SOURCE_DIR}/build/${TARGET_NAME}" )
target_link_libraries( testsDLL Infectorpp2)