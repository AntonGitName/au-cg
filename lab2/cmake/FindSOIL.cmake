# - Locate SOIL library
# This module defines
# SOIL_LIBRARY, the name of the library to link against
# SOIL_FOUND
# SOIL_INCLUDE_DIR, where to find SOIL.h
# To Adding search path, set SOIL_ROOT_DIR as follows
# set(SOIL_ROOT_DIR "path/to/soil")
# or launch cmake with -DSOIL_ROOT_DIR="/path/to/SOIL_ROOT_DIR".
#
# author: Kazunori Kimura
# email : kazunori.abu@gmail.com
#
# revisions: github.com/zwookie

FIND_PATH( SOIL_INCLUDE_DIRS SOIL/SOIL.h /usr/include /usr/local/include $ENV{INCLUDE} )
FIND_LIBRARY( SOIL_LIBRARIES NAMES SOIL PATHS /usr/lib /usr/local/lib )

IF(SOIL_INCLUDE_DIRS)
    MESSAGE(STATUS "Found SOIL include dir: ${SOIL_INCLUDE_DIRS}")
ELSE(SOIL_INCLUDE_DIRS)
    MESSAGE(STATUS "Could NOT find SOIL headers.")
ENDIF(SOIL_INCLUDE_DIRS)

IF(SOIL_LIBRARIES)
    MESSAGE(STATUS "Found SOIL library: ${SOIL_LIBRARIES}")
ELSE(SOIL_LIBRARIES)
    MESSAGE(STATUS "Could NOT find SOIL library.")
ENDIF(SOIL_LIBRARIES)

IF(SOIL_INCLUDE_DIRS AND SOIL_LIBRARIES)
    SET(SOIL_FOUND "YES")
ELSE(SOIL_INCLUDE_DIRS AND SOIL_LIBRARIES)
    SET(SOIL_FOUND "NO")
    IF(SOIL_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find SOIL. Please install SOIL")
    ENDIF(SOIL_FIND_REQUIRED)
ENDIF(SOIL_INCLUDE_DIRS AND SOIL_LIBRARIES)