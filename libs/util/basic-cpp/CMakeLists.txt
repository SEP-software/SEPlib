cmake_minimum_required(VERSION 3.5)
project(Generic-cpp)

find_package(Boost 1.40 COMPONENTS program_options unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCES calcBlock.cpp basicLoop.cpp doubleLoop.cpp sinc.cpp maps.cpp)
set(INCLUDES calcBlock.h basicLoop.h doubleLoop.h sinc.h maps.h)

add_library(sepBasicCpp ${SOURCES} ${INCLUDES})
target_link_libraries(sepBasicCpp genericCpp sepVector)

if(BUILD_TEST)
add_executable( test_calcBlock  test_calcBlock.cpp)
target_link_libraries( test_calcBlock sepBasicCpp gtest gtest_main gtest)
add_test(NAME  test_calcBlock COMMAND  test_calcBlock)

add_executable(test_basicLoop test_basicLoop.cpp)
target_link_libraries(test_basicLoop sepBasicCpp gtest gtest_main gtest)
add_test(NAME basicLoop COMMAND test_basicLoop)

add_executable(testSinc testSinc.cpp)
target_link_libraries(testSinc sepBasicCpp gtest gtest_main gtest)
add_test(NAME testSinc COMMAND testSinc)

endif(BUILD_TEST)



install(TARGETS sepBasicCpp  DESTINATION lib)


