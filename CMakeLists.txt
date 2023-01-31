cmake_minimum_required(VERSION 3.25)

project(
  mazengine
  VERSION 0.1.0
  LANGUAGES C CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(MAZENGINE_LIBRARY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
string(APPEND MAZENGINE_LIBRARY "/libmazengine.so")

message(STATUS "HEY THERE!!! ${MAZENGINE_LIBRARY}")

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

find_package(SDL2 REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(yaml-cpp REQUIRED)

add_subdirectory(src)
