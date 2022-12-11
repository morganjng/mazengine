#ifndef TILE_LAYER_H_
#define TILE_LAYER_H_

#include <iostream>
#include <vector>
#include <yaml-cpp/yaml.h>

namespace mazengine {

	class TileLayer {
	public:
		std::vector<std::vector<int>> tile_ids;
		std::string tile_type;
		int height;
		int width;
		TileLayer(YAML::Node tiles) {
			// std::cout << tiles << std::endl;
			tile_ids = *new std::vector<std::vector<int>>();
			width = tiles["width"].as<int>();
			height = tiles["height"].as<int>();
			for (int i = 0; i < height; i++) {
				tile_ids.push_back(tiles["tiles"][i].as<std::vector<int>>());
			}
			tile_type = tiles["type"].as<std::string>();
		}
	};

}; // namespace mazengine

#endif // EBLAYER_H_
