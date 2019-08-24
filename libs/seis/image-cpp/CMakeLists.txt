cmake_minimum_required(VERSION 3.5)

set(CMAKE_MACOSX_RPATH 1)
find_package(Boost 1.40 COMPONENTS program_options unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCES kirchTime.cpp)
set(INCLUDES kirchTime.h)

add_library(sepImageCpp ${SOURCES} ${INCLUDES})


target_link_libraries(sepImageCpp genericCpp hypercube tbb ${EXTERNAL_TARGETS})

install(TARGETS sepImageCpp DESTINATION lib)


