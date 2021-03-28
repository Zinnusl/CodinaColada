# CMakeList.txt : CMake project for CodingColada, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CodingColada")

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true src/*.h src/*.cpp)

# Add source to this project's executable.
add_executable (CodingColada ${SOURCES})

# TODO: Add tests and install targets if needed.

find_package(glfw3)
target_link_libraries(CodingColada PRIVATE glfw)

find_package(glad CONFIG REQUIRED)
target_link_libraries(CodingColada PRIVATE glad::glad)

find_package(glm CONFIG REQUIRED)
target_link_libraries(CodingColada PRIVATE glm::glm)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(CodingColada PRIVATE imgui::imgui) 

find_package(asio CONFIG REQUIRED)
target_link_libraries(CodingColada PRIVATE asio asio::asio)


#enable usage of VS Profiler
SET_TARGET_PROPERTIES(CodingColada PROPERTIES LINK_FLAGS "/PROFILE")

#c++17
set (CMAKE_CXX_STANDARD 17)