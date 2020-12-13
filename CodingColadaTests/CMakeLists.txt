# CMakeList.txt : CMake project for CodingColada, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true ../CodingColada/*.h ../CodingColada/*.cpp)
#list(REMOVE_ITEM SOURCES "../CodingColada/main.cpp")
list(FILTER SOURCES EXCLUDE REGEX "main\.cpp")
message("${SOURCES}")

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

# Add source to this project's executable.
add_executable (CodingColadaTests ${TEST_SOURCES} ${SOURCES})

# TODO: Add tests and install targets if needed.

find_path(BOOST_DI_INCLUDE_DIRS "boost/di.hpp")
target_include_directories(CodingColadaTests PRIVATE ${BOOST_DI_INCLUDE_DIRS})

find_package(GTest CONFIG REQUIRED)
target_link_libraries(CodingColadaTests PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)