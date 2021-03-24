# CMakeList.txt : CMake project for CodingColada, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CodingColada")

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true src/*.h src/*.cpp)

# Add source to this project's executable.
add_executable (CodingColada ${SOURCES})

# TODO: Add tests and install targets if needed.

find_package(SDL2)
target_link_libraries(CodingColada PRIVATE SDL2::SDL2 SDL2::SDL2main)

find_package(glfw3)
target_link_libraries(CodingColada PRIVATE glfw)

find_package(glad CONFIG REQUIRED)
target_link_libraries(CodingColada PRIVATE glad::glad)

find_package(glm CONFIG REQUIRED)
target_link_libraries(CodingColada PRIVATE glm::glm)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(CodingColada PRIVATE imgui::imgui) 