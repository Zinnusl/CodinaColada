# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("CodingColada")

# Include sub-projects.
add_subdirectory ("CodingColada")
add_subdirectory ("CodingColadaTests")

# REQUIRED PACKAGES:
# vcpkg install boost-di:x64-windows
# vcpkg install gtest:x64-windows
# vcpkg install sdl2:x64-windows 
# vcpkg install glfw3:x64-windows