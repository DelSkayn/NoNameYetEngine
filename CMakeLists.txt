cmake_minimum_required(VERSION 2.6)

project(NNYEngine)

# Version

set(NNYEngine_VERSION_MAJOR 0)
set(NNYEngine_VERSION_MINOR 0)
set(NNYEngine_VERSION_PATCH 1)

#set(CMAKE_VERBOSE_MAKEFILE ON)

#default definitions

add_definitions(
    -c 
    -Wall
    -std=c++0x
    -pedantic
    )

#Build Type 

if ( CMAKE_BUILD_TYPE STREQUAL "" )
    set(CMAKE_BUILD_TYPE 
            "Debug")
        
endif( CMAKE_BUILD_TYPE STREQUAL "" )

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions( -O3 )
endif(CMAKE_BUILD_TYPE STREQUAL "Release")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(
        -DDEBUG
        -g
        )
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

if(CMAKE_BUILD_TYPR STREQUAL "RDebug")
    add_definitions(
        -DDEBUG
        -DRDEBUG
        -g
        )
endif(CMAKE_BUILD_TYPR STREQUAL "RDebug")


SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wl,--no-as-needed")

#Include files

file(GLOB_RECURSE HDRS ${NNYEngine_SOURCE_DIR}/src/*.h)

file(GLOB_RECURSE SRCS ${NNYEngine_SOURCE_DIR}/src/*.cpp)

#Executable

add_executable(NNYEngine ${HDRS} ${SRCS})

#External libaries 

SET(NNYEngine_CMAKE_DIR "${NNYEngine_SOURCE_DIR}/cmake")

# OpenGL
find_package(OpenGL REQUIRED)

find_package(Threads REQUIRED)

# GLEW
INCLUDE(${NNYEngine_CMAKE_DIR}/FindGLFW.cmake)

# Assimp 
INCLUDE(${NNYEngine_CMAKE_DIR}/FindAssimp.cmake)

# GLFW 
INCLUDE(${NNYEngine_CMAKE_DIR}/FindGLEW.cmake)


# Define the include DIRs
include_directories(
	${NNYEngine_SOURCE_DIR}/headers
	${NNYEngine_SOURCE_DIR}/sources
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIRS}
    ./install/include
)

# Define the link libraries
target_link_libraries( NNYEngine
    ${GLFW_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${GLEW_LIBRARIES}
	${OPENGL_LIBRARIES}
    ${ASSIMP_LIBRARIES}
)

