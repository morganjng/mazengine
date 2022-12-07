#ifndef TILE_GAME_H_
#define TILE_GAME_H_

#include "mazengine.h"
#include "tile_entity.h"
#include "tile_map.h"
#include "tile_player.h"
#include "tile_renderer.h"
#include <string>
#include <yaml-cpp/yaml.h>

namespace mazengine {

	class TileGame : public Game {
	private:
		std::string data_path;
		std::string img_path;
		std::string audio_path;
		std::string map_key;
		std::string following_key;
		TileEntity *following;
		TileRenderer *tiles;
		tile_map *current_map;
		YAML::Node map_yaml;
		int tile_size;
		int tile_width;
		int tile_height;
		tile_player *player;

	public:
		TileGame(int tile_sz, int tile_w, int tile_h) {
			data_path = "UNSET";
			img_path = "UNSET";
			audio_path = "UNSET";
			following = nullptr;
			current_map = nullptr;
			tiles = nullptr;
			tile_size = tile_sz;
			tile_width = tile_w;
			tile_height = tile_h;
			internal_width = tile_w * tile_sz;
			internal_height = tile_h * tile_sz;
		}
		int InitialTick();
		int Tick(int status);
		int Draw();
		int Present();
		int React(int idx);
	};

}; // namespace mazengine

#endif
