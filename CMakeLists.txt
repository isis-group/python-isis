project(isis-python)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

###########################################################
# find and configure the isis core library
###########################################################
FIND_PACKAGE(ISIS REQUIRED)
INCLUDE_DIRECTORIES(${ISIS_INCLUDE_DIRS})

###############################################################################
# add global options
###############################################################################
ADD_DEFINITIONS(-D_ENABLE_LOG=1)
ADD_DEFINITIONS(-D_ENABLE_DEBUG=0)

find_package(PythonInterp)

set(PYTHON_VERSIONS ${PYTHON_EXECUTABLE} CACHE STRING "Python interpreters to install the python interace for")

find_package(Boost REQUIRED COMPONENTS python)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})

add_subdirectory(isis)

