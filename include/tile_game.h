#ifndef TILE_GAME_H_
#define TILE_GAME_H_

#include "mazengine.h"
#include "player.h"
#include "tile_map.h"
#include "tile_renderer.h"
#include <string>
#include <yaml-cpp/yaml.h>

class tile_game : public mazengine::game {
  private:
    std::string data_path;
    std::string img_path;
    std::string audio_path;
    std::string map_key;
    std::string following_key;
    mazengine::entity *following;
    tile_renderer *tiles;
    tile_map *current_map;
    YAML::Node map_yaml;
    int tile_size;
    int tile_width;
    int tile_height;
    tile_player *player;

  public:
    tile_game(int tile_sz, int tile_w, int tile_h) {
        data_path = "UNSET";
        img_path = "UNSET";
        audio_path = "UNSET";
        following = nullptr;
        current_map = nullptr;
        tiles = nullptr;
        tile_size = tile_sz;
        tile_width = tile_w;
        tile_height = tile_h;
    }
    void set_data_path(std::string path);
    void set_img_path(std::string path);
    void set_audio_path(std::string path);
    int initial_tick();
    int tick(std::vector<mazengine::button> *presses,
             std::vector<mazengine::button> *releases);
    int draw();
    int present();
};

#endif
