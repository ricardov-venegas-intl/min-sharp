# CMakeList.txt : CMake project for min-sharp-runtime, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("min-sharp-runtime")

# Add source to this project's executable.
add_library (min-sharp-runtime "min-sharp-runtime.cpp" "min-sharp-runtime.h")

# TODO: Add tests and install targets if needed.
