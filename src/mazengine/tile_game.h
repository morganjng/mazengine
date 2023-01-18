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
		String data_path;
		String img_path;
		String audio_path;
		String map_key;
		String following_key;
		TileEntity *following;
		TileRenderer *tiles;
		TileMap *current_map;
		YAML::Node map_yaml;
		int tile_size;
		int tile_width;
		int tile_height;
		TilePlayer *player;

	public:
		TileGame(int tile_sz, int tile_w, int tile_h, String _name,
				 Game *_parent)
			: Game(_name, _parent) {
			auto paths = Mazzycat::GetPaths();
			data_path = paths["data"];
			img_path = paths["img"];
			audio_path = paths["audio"];
			YAML::Node data = YAML::LoadFile(data_path + _name + ".yaml");
			following = nullptr;
			current_map = nullptr;
			tiles = nullptr;
			tile_size = data["tile_size"].as<int>();
			tile_width = data["tile_width"].as<int>();
			tile_height = data["tile_height"].as<int>();
			internal_width = tile_width * tile_size;
			internal_height = tile_height * tile_size;
		}
		int Tick(int status);
		int Draw();
		int Present();
		int React(int idx);
	};

}; // namespace mazengine

#endif
