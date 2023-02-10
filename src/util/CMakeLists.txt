add_executable(
  MZTileEditor
  tile_map_editor.cc
  )


set_target_properties(MZTileEditor PROPERTIES VERSION ${PROJECT_VERSION}
                                           SOVERSION ${PROJECT_VERSION_MAJOR})

target_include_directories(MZTileEditor SYSTEM PRIVATE ${SDL2_INCLUDE_DIRS})

target_include_directories(MZTileEditor SYSTEM PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})

target_include_directories(MZTileEditor SYSTEM PRIVATE ${SDL_MIXER_INCLUDE_DIRS})

target_include_directories(MZTileEditor SYSTEM PRIVATE ${SDL_TTF_INCLUDE_DIRS})

target_include_directories(MZTileEditor SYSTEM PRIVATE ${PYTHON_INCLUDE_DIRS})

target_include_directories(MZTileEditor SYSTEM PRIVATE ${Boost_INCLUDE_DIRS})

target_include_directories(MZTileEditor PUBLIC ${MAZENGINE_INCLUDES})

target_link_libraries(
  MZTileEditor
  PRIVATE SDL2
          SDL2_image
          ${YAML_CPP_LIBRARIES}
          ${SDL_MIXER_LIBRARIES}
          ${SDL_TTF_LIBRARIES}
          ${Boost_LIBRARIES}
          ${PYTHON_LIBRARIES})

target_link_libraries(MZTileEditor PRIVATE "mazengine")

if(MVSC)
  target_compile_options(MZTileEditor PUBLIC /W4 /WX)
else()
  target_compile_options(MZTileEditor PUBLIC -Wall -Wextra -Wpedantic -Werror)
endif()
