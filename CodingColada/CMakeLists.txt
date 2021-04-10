# CMakeList.txt : CMake project for CodingColada, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CodingColada")

include(../../vcpkg/scripts/buildsystems/vcpkg.cmake)

message(${PROJECT_SOURCE_DIR})
message(${PROJECT_SOURCE_DIR})

file(GLOB_RECURSE ENGINE_SOURCES LIST_DIRECTORIES true engine/*.h engine/*.cpp)
file(GLOB_RECURSE GAME_COMMON_SOURCES LIST_DIRECTORIES true game/common/*.h game/common/*.cpp)
file(GLOB_RECURSE GAME_CLIENT_SOURCES LIST_DIRECTORIES true game/client/*.h game/client/*.cpp)
file(GLOB_RECURSE GAME_SERVER_SOURCES LIST_DIRECTORIES true game/server/*.h game/server/*.cpp)

# Add source to this project's executable.
add_executable (Colada_Client ${ENGINE_SOURCES} ${GAME_COMMON_SOURCES} ${GAME_CLIENT_SOURCES})
add_executable (Colada_Server ${ENGINE_SOURCES} ${GAME_COMMON_SOURCES} ${GAME_SERVER_SOURCES})

# TODO: Add tests and install targets if needed.

find_package(glfw3)
target_link_libraries(Colada_Client PRIVATE glfw)
target_link_libraries(Colada_Server PRIVATE glfw)

find_package(glad CONFIG REQUIRED)
target_link_libraries(Colada_Client PRIVATE glad::glad)
target_link_libraries(Colada_Server PRIVATE glad::glad)

find_package(glm CONFIG REQUIRED)
target_link_libraries(Colada_Client PRIVATE glm::glm)
target_link_libraries(Colada_Server PRIVATE glm::glm)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(Colada_Client PRIVATE imgui::imgui) 
target_link_libraries(Colada_Server PRIVATE imgui::imgui) 

#find_package(asio CONFIG REQUIRED)
#target_link_libraries(Colada_Client PRIVATE asio asio::asio)
#target_link_libraries(Colada_Server PRIVATE asio asio::asio)

#linux
find_library(fmod libfmodL.so HINTS "${PROJECT_SOURCE_DIR}/lib")
target_link_libraries(Colada_Client PRIVATE ${fmod})
target_link_libraries(Colada_Server PRIVATE ${fmod})
#coppy libfmodL.so.12 to /usr/lib 

#enable usage of VS Profiler
#SET_TARGET_PROPERTIES(Colada_Client PROPERTIES LINK_FLAGS "/PROFILE")
#SET_TARGET_PROPERTIES(Colada_Server PROPERTIES LINK_FLAGS "/PROFILE")

#c++17
target_compile_features(Colada_Client PRIVATE cxx_std_17)
target_compile_features(Colada_Server PRIVATE cxx_std_17)


configure_file("${PROJECT_SOURCE_DIR}/lib/fmod.dll" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/lib/libfmodL.so" ${CMAKE_BINARY_DIR} COPYONLY)

# REQUIRED PACKAGES:
# vcpkg install glfw3:x64-windows
# vcpkg install glad:x64-windows
# vcpkg install glm:x64-windows
# vcpkg install imgui:x64-windows
# vcpkg install asio:x64-windows


#Are withing (can be built?) the FMOD examples download
#fmod api/core/lib/x64/fmod.dll
#fmod api/core/lib/x64/fmod_vc.lib
