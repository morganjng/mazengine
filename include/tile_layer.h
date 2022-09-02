#ifndef TILE_LAYER_H_
#define TILE_LAYER_H_

#include <iostream>
#include <vector>
#include <yaml-cpp/yaml.h>

using namespace mazengine;

class tile_layer {
public:
	std::vector<std::vector<int>> tile_ids;
	std::string tile_type;
	int height;
	int width;
	tile_layer(YAML::Node tiles) {
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

#endif // EBLAYER_H_
