add_library(
  mazengine SHARED
  audio.cc
  engine.cc
  font.cc
  game.cc
  geometry.cc
  igame.cc
  io_2d_mouse.cc
  io_2d_no_mouse.cc
  io_mouse.cc
  menu.cc
  texture.cc
  mazscript.cc
  tile_display.cc
  tile_editor.cc)

set_target_properties(mazengine PROPERTIES VERSION ${PROJECT_VERSION}
                                           SOVERSION ${PROJECT_VERSION_MAJOR})

target_include_directories(mazengine SYSTEM PRIVATE ${SDL2_INCLUDE_DIRS})

target_include_directories(mazengine SYSTEM PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})

target_include_directories(mazengine SYSTEM PRIVATE ${SDL_MIXER_INCLUDE_DIRS})

target_include_directories(mazengine SYSTEM PRIVATE ${SDL_TTF_INCLUDE_DIRS})

target_include_directories(mazengine SYSTEM PRIVATE ${PYTHON_INCLUDE_DIRS})

target_include_directories(mazengine SYSTEM PRIVATE ${Boost_INCLUDE_DIRS})

target_include_directories(mazengine PUBLIC ${MAZENGINE_INCLUDES})

target_link_libraries(
  mazengine
  PRIVATE SDL2
          SDL2_image
          ${YAML_CPP_LIBRARIES}
          ${SDL_MIXER_LIBRARIES}
          ${SDL_TTF_LIBRARIES}
          ${Boost_LIBRARIES}
          ${PYTHON_LIBRARIES})

if(MVSC)
  target_compile_options(mazengine PUBLIC /W4 /WX)
else()
  target_compile_options(mazengine PUBLIC -Wall -Wextra -Wpedantic -Werror -g)
endif()

add_subdirectory(util)
