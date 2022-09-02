#ifndef TILE_MAP_H_
#define TILE_MAP_H_

#include "entity.h"
#include "mazengine.h"
#include "tile_layer.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <yaml-cpp/yaml.h>

using namespace mazengine;

class tile_map {
private:
    std::vector<tile_layer> layers;
    std::vector<entity> objects;
    std::string map_key;
    YAML::Node map_node;
    int layer_count;

public:
    int bg_color;
    tile_map(std::string path, std::string map_key, SDL_Renderer *renderer) {
	this->map_key = map_key;
	map_node = YAML::LoadFile(path)[map_key];
	bg_color = map_node["bg_color"].as<int>();
	layers = std::vector<tile_layer>();
	objects = std::vector<entity>();
	layer_count = map_node["layers"]["count"].as<int>();
	for (int i = 0; i < layer_count; i++) {
	    layers.push_back(tile_layer(map_node["layers"][i]));
	    // std::cout << i << std::endl;
	}
	// std::cout << map_node["objects"] << std::endl;
	std::vector<std::string> object_names =
	    map_node["objects"]["names"].as<std::vector<std::string>>();
	for (std::string name : object_names) {
	    objects.push_back(
		*new entity(map_node["objects"][name]["type"].as<std::string>(),
			    map_node["objects"][name]["key"].as<std::string>(),
			    map_node["objects"][name]["id"].as<int>(),
			    map_node["objects"][name]["x"].as<int>(),
			    map_node["objects"][name]["y"].as<int>()));
	}
    };
    std::vector<tile_layer> *get_layers();
    std::vector<entity> *get_objects();
};

#endif // EBMAP_H_
