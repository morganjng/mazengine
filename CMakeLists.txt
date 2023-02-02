cmake_minimum_required(VERSION 3.25)

project(
  mazengine
  VERSION 0.1.0
  LANGUAGES C CXX)

message(STATUS "Current src dir ${CMAKE_CURRENT_SOURCE_DIR}")

set(MAZENGINE_INCLUDES "")
string(APPEND MAZENGINE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
string(APPEND MAZENGINE_INCLUDES "/include/mazengine")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(MAZENGINE_LIBRARY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
string(APPEND MAZENGINE_LIBRARY "/libmazengine.so")

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(PythonLibs REQUIRED)
find_package(
  Boost
  COMPONENTS python
  REQUIRED)

add_subdirectory(src)
