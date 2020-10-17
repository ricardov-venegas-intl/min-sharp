# CMakeList.txt : CMake project for min-sharp-runtime, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.c)

set(SOURCES ${SOURCES})

# Add source to this project's executable.
add_library(${BINARY}_lib STATIC ${SOURCES} )


