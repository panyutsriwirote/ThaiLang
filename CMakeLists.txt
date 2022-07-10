cmake_minimum_required(VERSION 3.23.1)
project(ThaiLang)
include(CTest)

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include_directories(./include)
add_executable(thai main.c object.c)

# add_test(NAME hello COMMAND thai)
# set_property(TEST hello PROPERTY PASS_REGULAR_EXPRESSION "^Hello World!")