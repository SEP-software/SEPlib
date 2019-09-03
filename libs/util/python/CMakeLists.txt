cmake_minimum_required(VERSION 3.5)
project(python-SEP-util)

include_directories(${Boost_INCLUDE_DIR})
pybind11_add_module(pySEPUtil MODULE pySEPUtil.cpp)
target_link_libraries(pySEPUtil PRIVATE sepImageCpp sepVelanCpp)
target_include_directories(
  pySEPUtil
  PUBLIC ${PYTHON_INCLUDE_DIR}
         ${pybind11_INCLUDE_DIR}
         $<INSTALL_INTERFACE:include>
         ${CMAKE_CURRENT_BINARY_DIR}/../core/external/genericIO
         ${CMAKE_CURRENT_SOURCE_DIR}/../core/external/genericIO/cpp
         ${CMAKE_CURRENT_SOURCE_DIR}/../core/external/genericIO/external/buffers/external/json
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../seis/velan-cpp>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../seis/image-cpp>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../basic-cpp>)

install(TARGETS pySEPUtil DESTINATION lib)

install(FILES KirchTime.py Vel3D.py	Loop.py DESTINATION lib/python)
