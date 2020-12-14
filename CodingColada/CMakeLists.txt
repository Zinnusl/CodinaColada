# CMakeList.txt : CMake project for CodingColada, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

# Add source to this project's executable.
add_executable (CodingColada ${SOURCES})

# TODO: Add tests and install targets if needed.

find_path(BOOST_DI_INCLUDE_DIRS "boost/di.hpp")
target_include_directories(CodingColada PRIVATE ${BOOST_DI_INCLUDE_DIRS})

find_package(SDL2)
target_link_libraries(CodingColada PRIVATE SDL2::SDL2 SDL2::SDL2main)