cmake_minimum_required(VERSION 3.5)

set(CMAKE_MACOSX_RPATH 1)
include_directories(${Boost_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../velan-cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../util/basic-cpp)
set(SOURCES stack.cpp floatFilter.cpp)
set(INCLUDES stack.h floatFilter.h)

add_library(sepFilterCpp ${SOURCES} ${INCLUDES})


target_link_libraries(sepFilterCpp sepBasicCpp genericCpp hypercube tbb ${EXTERNAL_TARGETS})

install(TARGETS sepFilterCpp DESTINATION lib)


