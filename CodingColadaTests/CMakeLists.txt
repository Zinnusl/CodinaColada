﻿# CMakeList.txt : CMake project for CodingColada, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ../CodingColada/src/*.h ../CodingColada/src/*.cpp)
#list(REMOVE_ITEM SOURCES "../CodingColada/main.cpp")
list(FILTER SOURCES EXCLUDE REGEX "main\.cpp")
message("CodingColadaTests Sources:")
message("${SOURCES}")

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

# Add source to this project's executable.
add_executable (CodingColadaTests ${TEST_SOURCES} ${SOURCES})

# TODO: Add tests and install targets if needed.

find_path(BOOST_DI_INCLUDE NAMES "boost/di.hpp" PATHS ../di/include/)
target_include_directories(CodingColadaTests PRIVATE ${BOOST_DI_INCLUDE})


find_path(BOOST_DI_INCLUDE_EXTENSION NAMES "boost/di/extension/injector.hpp" PATHS ../di/extension/include/)
target_include_directories(CodingColadaTests PRIVATE ${BOOST_DI_INCLUDE_EXTENSION})


find_package(GTest CONFIG REQUIRED)
target_link_libraries(CodingColadaTests PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

find_package(SDL2)
target_link_libraries(CodingColadaTests PRIVATE SDL2::SDL2 SDL2::SDL2main)

find_package(glfw3)
target_link_libraries(CodingColadaTests PRIVATE glfw)

find_package(glad CONFIG REQUIRED)
target_link_libraries(CodingColada PRIVATE glad::glad)

find_package(glm CONFIG REQUIRED)
target_link_libraries(CodingColada PRIVATE glm)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(CodingColada PRIVATE imgui::imgui) 