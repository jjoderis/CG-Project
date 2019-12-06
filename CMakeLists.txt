cmake_minimum_required(VERSION 3.10)

#specify C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Weffc++ -Wextra -Wsign-conversion -Werror -pedantic-errors")

#Project Name
project(CG-Project)

FIND_PACKAGE( OpenGL )
FIND_PACKAGE( glfw3 3.2 REQUIRED )

set( INCLUDE_DIR ${PROJECT_SOURCE_DIR}/includes )
set( GLEW_DIR ${PROJECT_SOURCE_DIR}/glew )

set( PROJECT_SOURCES 
        ${INCLUDE_DIR}/LoadShaders/LoadShaders.cpp    
)

#add the glew subdirectory
add_subdirectory( ${GLEW_DIR} )

#add executable
add_executable(CG-Project main.cpp ${PROJECT_SOURCES})

target_link_libraries(CG-Project PUBLIC ${OPENGL_LIBRARIES} glfw Glew)

#add the binary tree to the search path for include files
target_include_directories(CG-Project PUBLIC
                          ${GLEW_DIR}
                          ${INCLUDE_DIR}/LoadShaders
                          )