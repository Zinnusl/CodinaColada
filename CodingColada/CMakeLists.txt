﻿# CMakeList.txt : CMake project for CodingColada, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false src/*.h src/*.cpp)

# Add source to this project's executable.
message("CodingColada Sources:")
message("${SOURCES}")
add_executable (CodingColada ${SOURCES})

# TODO: Add tests and install targets if needed.

find_path(BOOST_DI_INCLUDE NAMES "boost/di.hpp" PATHS ../di/include/)
target_include_directories(CodingColada PRIVATE ${BOOST_DI_INCLUDE})

find_path(BOOST_DI_INCLUDE_EXTENSION NAMES "boost/di/extension/injector.hpp" PATHS ../di/extension/include/)
target_include_directories(CodingColada PRIVATE ${BOOST_DI_INCLUDE_EXTENSION})

find_package(SDL2)
target_link_libraries(CodingColada PRIVATE SDL2::SDL2 SDL2::SDL2main)

find_package(glfw3)
target_link_libraries(CodingColada PRIVATE glfw)

find_package(glad CONFIG REQUIRED)
target_link_libraries(CodingColada PRIVATE glad::glad)

find_package(glm CONFIG REQUIRED)
target_link_libraries(CodingColada PRIVATE glm)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(CodingColada PRIVATE imgui::imgui) 