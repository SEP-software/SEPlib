cmake_minimum_required(VERSION 3.5)

set(CMAKE_MACOSX_RPATH 1)
include_directories(${Boost_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../velan-cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../util/basic-cpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../../core/external/genericIO/external/sepVector/)
set(SOURCES spike.cpp )
set(INCLUDES spike.h)

add_library(sepModelCpp ${SOURCES} ${INCLUDES})


target_link_libraries(sepModelCpp sepBasicCpp genericCpp sepVector hypercube tbb ${EXTERNAL_TARGETS})

install(TARGETS sepModelCpp DESTINATION lib)


