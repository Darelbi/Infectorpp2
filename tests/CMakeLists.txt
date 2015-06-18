#=============================================================================
# Welcome to BadeEngine3D Build system. ./tests
#=============================================================================
cmake_minimum_required( VERSION 2.8)
project( infectorppTests)

#-----------------------------------CONFIGURE---------------------------------
#-----------------------------------------------------------------------------
include( EnableCpp11)
include( GenerateTestDriver)

include_directories("../include/Infectorpp/")

generate_test_driver( tests)
set( ENV{PATH} "$ENV{PATH};${CMAKE_SOURCE_DIR}/build/${TARGET_NAME}" )
target_link_libraries( tests libInfectorpp2)