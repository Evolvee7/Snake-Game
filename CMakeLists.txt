cmake_minimum_required(VERSION 3.7)

project(snake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(snake src/main.cpp src/Snake.cpp src/Pellet.cpp src/Game.cpp src/Utilities.cpp)

target_include_directories(snake PRIVATE include/)
target_link_libraries(snake ${SDL2_LIBRARIES})