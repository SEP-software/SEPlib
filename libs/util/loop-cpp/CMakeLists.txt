cmake_minimum_required(VERSION 3.5)
project(Generic-cpp)

find_package(Boost 1.40 COMPONENTS program_options unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCES basicLoop.cpp doubleLoop.cpp)
set(INCLUDES basicLoop.h doubleLoop.h)

add_library(sepLoopCpp ${SOURCES} ${INCLUDES})
target_link_libraries(sepLoopCpp sepVector)


install(TARGETS sepLoopCpp  DESTINATION lib)


