#ifndef PLAYER_H_
#define PLAYER_H_

#include "mazengine.h"
#include "tile_renderer.h"
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

using namespace mazengine;

class tile_player {
	private:
		bool directions[4];

	public:
		int position_x;
		int position_y;
		int center_offset_x;
		int center_offset_y;
		int speed;
		int id;
		std::string key;
		std::string map_key;
		tile_set *tileset;

		tile_player(std::string data_path) {
			YAML::Node data = YAML::LoadFile(data_path + "player.yaml");
			// std::cout << data << std::endl;
			position_x = data["position_x"].as<int>();
			position_y = data["position_y"].as<int>();
			center_offset_x = data["center_offset_x"].as<int>();
			center_offset_y = data["center_offset_y"].as<int>();
			speed = data["speed"].as<int>();
			id = data["id"].as<int>();
			key = data["key"].as<std::string>();
			map_key = data["map_key"].as<std::string>();
			directions[0] = false;
			directions[1] = false;
			directions[2] = false;
			directions[3] = false;
		}

		void tick(std::vector<mazengine::button> *presses,
				  std::vector<mazengine::button> *releases);
};

#endif // PLAYER_H_
