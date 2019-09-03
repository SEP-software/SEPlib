cmake_minimum_required(VERSION 3.5)
project(Generic-cpp)

find_package(Boost 1.40 COMPONENTS program_options unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../core/external/genericIO/cpp)

set(SOURCES calcBlock.cpp basicLoop.cpp doubleLoop.cpp sinc.cpp)
set(INCLUDES calcBlock.h basicLoop.h doubleLoop.h sinc.h)

add_library(sepBasicCpp ${SOURCES} ${INCLUDES})
target_link_libraries(sepBasicCpp sepVector)


install(TARGETS sepBasicCpp  DESTINATION lib)


