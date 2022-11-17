cmake_minimum_required(VERSION 3.5)

set(CMAKE_MACOSX_RPATH 1)
include_directories(${Boost_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../velan-cpp)

set(SOURCES kirchTime.cpp)
set(INCLUDES kirchTime.h)

add_library(sepImageCpp ${SOURCES} ${INCLUDES})


target_link_libraries(sepImageCpp sepVelanCpp genericCpp hypercube tbb ${EXTERNAL_TARGETS})

install(TARGETS sepImageCpp DESTINATION lib)


