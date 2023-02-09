add_executable(MazTEST
  test.cpp)

link_directories(${CMAKE_BINARY_DIR})

set_target_properties(MazTEST PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(MazTEST SYSTEM PRIVATE ${SDL2_INCLUDE_DIRS})

target_include_directories(MazTEST SYSTEM
                           PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})

target_include_directories(MazTEST SYSTEM
                           PRIVATE ${SDL_IMAGE_INCLUDE_DIRS})

target_include_directories(MazTEST SYSTEM
                           PRIVATE ${SDL_MIXER_INCLUDE_DIRS})

target_include_directories(MazTEST SYSTEM PRIVATE ${SDL_TTF_INCLUDE_DIRS})

target_include_directories(MazTEST SYSTEM PRIVATE ${Boost_INCLUDE_DIRS})

target_include_directories(MazTEST SYSTEM PRIVATE ${PYTHON_INCLUDE_DIRS})

target_include_directories(
  MazTEST PRIVATE ${CMAKE_SOURCE_DIR}/include/mazengine)

target_link_libraries(
  MazTEST
  PRIVATE SDL2
          SDL2_image
          ${YAML_CPP_LIBRARIES}
          ${SDL_MIXER_LIBRARIES}
          ${SDL_TTF_LIBRARIES}
          ${Boost_LIBRARIES}
          ${PYTHON_LIBRARIES})

target_link_libraries(MazTEST PRIVATE "mazengine")

if(MVSC)
  target_compile_options(MazTEST PUBLIC /W4 /WX)
else()
  target_compile_options(MazTEST PUBLIC -Wall -Wextra -Wpedantic -Werror)
endif()
