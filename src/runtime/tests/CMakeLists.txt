# CMakeList.txt : CMake project for min-sharp-runtime, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(BINARY ${CMAKE_PROJECT_NAME}_tst)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES true *.h *.c )

set(SOURCES ${TEST_SOURCES})

#target_link_libraries(min-sharp-runtime-tests min-sharp-runtime)

# Add source to this project's executable.
add_executable(${BINARY} ${TEST_SOURCES})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib)

