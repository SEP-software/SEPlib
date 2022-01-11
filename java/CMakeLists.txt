project(SEPLIB-java)
cmake_minimum_required(VERSION 3.8)

set(SEPlib-java_MAJOR_VERSION 9)
set(SEPlib-java_MINOR_VERSION 0)
set(SEPlib-java_VERSION_STRING
  ${SEPlib-java_MAJOR_VERSION}.${SEPlib-io_MINOR_VERSION})

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()


find_package(Java)
find_package(JNI)

if(JNI_FOUND AND Java_JAVAC_EXECUTABLE AND Java_JAVAH_EXECUTABLE AND Java_JAR_EXECUTABLE AND Java_JAVADOC_EXECUTABLE)
INCLUDE(UseJava)
add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(main)
endif(JNI_FOUND AND Java_JAVAC_EXECUTABLE AND Java_JAVAH_EXECUTABLE AND Java_JAR_EXECUTABLE AND Java_JAVADOC_EXECUTABLE)




include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${SEPlib-java_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${SEPlib-java_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_NAME "SEPlib-java")
set(CPACK_PACKAGE_CONTACT "Robert Clapp")
include(CPack)
