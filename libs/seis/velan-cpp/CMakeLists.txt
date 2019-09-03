cmake_minimum_required(VERSION 3.5)

set(CMAKE_MACOSX_RPATH 1)
find_package(Boost 1.40 COMPONENTS program_options unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../util/basic-cpp)

set(SOURCES vel3D.cpp nmo.cpp)
set(INCLUDES vel3D.h nmo.h)

add_library(sepVelanCpp ${SOURCES} ${INCLUDES})


target_link_libraries(sepVelanCpp sepBasicCpp genericCpp hypercube tbb ${EXTERNAL_TARGETS})

install(TARGETS sepVelanCpp DESTINATION lib)


