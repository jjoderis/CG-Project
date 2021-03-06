cmake_minimum_required(VERSION 3.10)

#specify C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic-errors")

#set option to build tests or the project from command line
option(BUILD_TESTS "BUILD_TESTS" OFF)

#Project Name
project(CG-Project)

#needed for GLEW in Travis
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

FIND_PACKAGE( OpenGL )
FIND_PACKAGE( glfw3 3.2 REQUIRED )

set( INCLUDE_DIR ${PROJECT_SOURCE_DIR}/includes )
set( GLEW_DIR ${PROJECT_SOURCE_DIR}/glew )
set( STB_DIR ${PROJECT_SOURCE_DIR}/stb )
set( TEST_DIR ${PROJECT_SOURCE_DIR}/test )

set( PROJECT_INCLUDES 
    ${INCLUDE_DIR}/framework
    ${INCLUDE_DIR}/framework/core
    ${INCLUDE_DIR}/helpers
    ${INCLUDE_DIR}/mathematics
    ${INCLUDE_DIR}
    examples
)

#add the glew subdirectory
add_subdirectory( ${GLEW_DIR} )
add_subdirectory( ${STB_DIR} )
add_subdirectory( ${INCLUDE_DIR}/mathematics )
add_subdirectory( ${INCLUDE_DIR}/framework/core )
add_subdirectory( ${INCLUDE_DIR}/framework/OpenGL )
add_subdirectory( ${INCLUDE_DIR}/helpers )

if(NOT BUILD_TESTS)

    #add executable
    add_executable(CG-Project main.cpp)

    target_link_libraries(CG-Project PUBLIC ${OPENGL_LIBRARIES} glfw Glew Math_Util CG_Framework_Core CG_Framework_OpenGL CG_Helper_Functions STB)

    target_include_directories(CG-Project PUBLIC
        ${GLEW_DIR}
        ${STB_DIR}
        ${PROJECT_INCLUDES}
    )

endif()

##########################
#GTest
##########################

#only do this if BUILD_TESTS is set
if(BUILD_TESTS)

    # Download and unpack googletest at configure time
    configure_file(${TEST_DIR}/CMakeLists.txt googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
    if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
    if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif()

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                    ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                    EXCLUDE_FROM_ALL)

    # The gtest/gtest_main targets carry header search path
    # dependencies automatically when using CMake 2.8.11 or
    # later. Otherwise we have to add them here ourselves.
    if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
    endif()

    # Now simply link against gtest or gtest_main as needed. Eg
    add_executable(unitTests ${TEST_FILES})
    target_link_libraries(unitTests gtest_main Math_Util CG_Framework_Core CG_Framework_OpenGL CG_Helper_Functions)
    add_test(NAME example_test COMMAND unitTests)

    target_include_directories(unitTests PUBLIC
        ${PROJECT_INCLUDES}
    )

endif()
