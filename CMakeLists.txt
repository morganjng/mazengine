cmake_minimum_required(VERSION 3.14...3.25)

project(
  Mazengine
  VERSION 0.1.0
  DESCRIPTION "A scriptable and easy-to-use game engine"
  LANGUAGES CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_EXTENSIONS OFF)

  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  include(CTest)

  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    massage(STATUS "Doxygen not found, not building docs.")
  endif()
endif()

include(FetchContent)

find_package(SDL2 REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(Ruby REQUIRED)
find_package(Rice REQUIRED)

add_subdirectory(src)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  add_subdirectory(test)
endif()
