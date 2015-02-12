SET( GLFW_SEARCH_PATHS
    ${GLFW_LOCATION}
    ./lib/GLFW
    $ENV{PROGRAMFILES}/GLFW
    "$ENV{PROGRAMFILES(X86)}/GLFW"
    /usr/local
    /usr
    /opt
    /sw
    /opt/local
    /opt/csw
    )

FIND_PATH( GLFW_INCLUDE_DIRS
    NAMES
        GL/glfw.h
        GLFW/glfw3.h
    PATHS
        ${GLFW_SEARCH_PATHS}
    PATH_SUFFIXES
        include
    DOC
        "The directory of the glfw.h file"
    )

FIND_LIBRARY( GLFW_LIBRARIES
    NAMES
        glfw3 libglfw3.a
    PATHS
        ${GLFW_SEARCH_PATHS}
    PATH_SUFFIXES
        lib
        lib64
        lib/x86
        lib/x64
    DOC
        "The GLFW lib"
    )

find_package(X11 REQUIRED)

if(NOT X11_Xrandr_FOUND)
    message(FATAL_ERROR "Xrandr library not found - required for GLFW")
endif()

if(NOT X11_xf86vmode_FOUND)
    message(FATAL_ERROR "xf86vmode library not found - required for GLFW")
endif()

if(NOT X11_Xcursor_FOUND)
    message(FATAL_ERROR "Xcursor library not found - required for GLFW")
endif()

list(APPEND GLFW_x11_LIBRARY "${X11_Xrandr_LIB}" "${X11_Xxf86vm_LIB}" "${X11_Xcursor_LIB}" "${CMAKE_THREAD_LIBS_INIT}" -lrt -lXi)


IF( GLFW_INCLUDE_DIRS AND GLFW_LIBRARIES )
    SET( GLFW_FOUND TRUE)
    MESSAGE(STATUS "Looking for Glfw - found")
    set(GLFW_LIBRARIES "${GLFW_LIBRARIES}" 
                       "${GLFW_x11_LIBRARY}")
ELSE ( GLFW_INCLUDE_DIRS AND GLFW_LIBRARIES )
    SET( GLFW_FOUND FALSE)
    MESSAGE(STATUS "Looking for Glfw - not found")
ENDIF( GLFW_INCLUDE_DIRS AND GLFW_LIBRARIES )
