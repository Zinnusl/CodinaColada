# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

message("Start outer Makelist")
# Include sub-projects.
add_subdirectory ("CodingColada")

# REQUIRED PACKAGES:
# vcpkg install glfw3:x64-windows
# vcpkg install glad:x64-windows
# vcpkg install glm:x64-windows
# vcpkg install imgui:x64-windows
# vcpkg install asio:x64-windows


#Are withing (can be built?) the FMOD examples download
#fmod api/core/lib/x64/fmod.dll
#fmod api/core/lib/x64/fmod_vc.lib