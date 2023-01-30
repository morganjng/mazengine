add_library(
  mazengine SHARED
  audio.cc
  engine.cc
  game.cc
  igame.cc
  io_2d_no_mouse.cc
  menu.cc
  ugame.cc
  font.cc
  geometry.cc
  io_2d_mouse.cc
  io_mouse.cc
  mazzycat.cc
  texture.cc)

target_include_directories(mazengine PUBLIC ../include/mazengine)

target_include_directories(
  mazengine SYSTEM PUBLIC ${SDL_IMAGE_INCLUDE_DIRS} ${SDL_MIXER_INCLUDE_DIRS}
                          ${SDL2_INCLUDE_DIRS} ${SDL_TTF_INCLUDE_DIRS})

target_link_libraries(mazengine INTERFACE Ruby SDL2 SDL_img SDL_mixer SDL_ttf
                                          yaml-cpp)

set_target_properties(mazengine PROPERTIES VERSION ${PROJECT_VERSION})

if(MVSC)
  target_compile_options(mazengine PUBLIC /W4 /WX)
else()
  # target_compile_options(mazengine PUBLIC -Wall -Wextra -Wpedantic -Werror)
endif()
