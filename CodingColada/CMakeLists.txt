# CMakeList.txt : CMake project for CodingColada, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


# Add source to this project's executable.
add_executable (CodingColada "CodingColada.cpp" "CodingColada.h" "App.h" "App.cpp")

# TODO: Add tests and install targets if needed.

find_path(BOOST_DI_INCLUDE_DIRS "boost/di.hpp")
target_include_directories(CodingColada PRIVATE ${BOOST_DI_INCLUDE_DIRS})