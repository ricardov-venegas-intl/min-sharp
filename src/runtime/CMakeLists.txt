# CMakeList.txt : CMake project for min-sharp-runtime, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("min-sharp-runtime")

include_directories("min-sharp-runtime")
# Add source to this project's executable.
add_subdirectory("min-sharp-runtime")

add_subdirectory("tests")

# TODO: Add tests and install targets if needed.
