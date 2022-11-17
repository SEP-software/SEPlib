cmake_minimum_required(VERSION 3.5)
project(Generic-cpp)

include_directories(${Boost_INCLUDE_DIR})

set(SOURCES calcBlock.cpp basicLoop.cpp doubleLoop.cpp sinc.cpp maps.cpp)
set(INCLUDES calcBlock.h basicLoop.h doubleLoop.h sinc.h maps.h)

add_library(sepBasicCpp ${SOURCES} ${INCLUDES})
target_link_libraries(sepBasicCpp genericCpp sepVector)



install(TARGETS sepBasicCpp  DESTINATION lib)


