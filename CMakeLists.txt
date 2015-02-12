cmake_minimum_required(VERSION 2.6)

project(ImpactEngine)

# Version

set(ImpactEngine_VERSION_MAJOR 0)
set(ImpactEngine_VERSION_MINOR 0)
set(ImpactEngine_VERSION_PATCH 1)

#set(CMAKE_VERBOSE_MAKEFILE ON)

#default definitions

add_definitions(
    -c 
    -Wall
    -std=gnu++11
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

file(GLOB_RECURSE HDRS ${ImpactEngine_SOURCE_DIR}/src/*.h)

file(GLOB_RECURSE SRCS ${ImpactEngine_SOURCE_DIR}/src/*.cpp)

#Executable

add_executable(ImpactEngine ${HDRS} ${SRCS})

#External libaries 

SET(ImpactEngine_CMAKE_DIR "${ImpactEngine_SOURCE_DIR}/cmake")

# OpenGL
find_package(OpenGL REQUIRED)

find_package(Threads REQUIRED)

# GLEW
INCLUDE(${ImpactEngine_CMAKE_DIR}/FindGLEW.cmake)

# GLFW 
find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)


# Define the include DIRs
include_directories(
	${ImpactEngine_SOURCE_DIR}/headers
	${ImpactEngine_SOURCE_DIR}/sources
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
)

# Define the link libraries
target_link_libraries( ImpactEngine
    ${GLFW_STATIC_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${GLEW_LIBRARIES}
	${OPENGL_LIBRARIES}
)

