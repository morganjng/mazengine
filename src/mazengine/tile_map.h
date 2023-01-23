/*
 * Map data class for tile based games
 */

#ifndef TILE_MAP_H_
#define TILE_MAP_H_

#include "mazengine.h"
#include "tile_entity.h"
#include "tile_layer.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <yaml-cpp/yaml.h>

namespace mazengine {
	/**
	 * Map of tiles for TileGames. Encompasses layers and objects to be
	 * displayed on the map.
	 * */
	class TileMap {
	private:
		std::vector<TileLayer> layers;	 /**< All layers. */
		std::vector<TileEntity> objects; /**< All objects. */
		String map_key;					 /**< Current map name. */
		YAML::Node map_node;			 /**< Data for current map. */
		int layer_count; /**< Amount of layers being displayed. */

	public:
		int bg_color; /**< RGBA color for background. */
		/**
		 * TileMap constructor. Takes path to yaml file and loads in all data.
		 * Needs reconfiguring.
		 * */
		TileMap(String path, String map_key, SDL_Renderer *renderer) {
			this->map_key = map_key;
			map_node = YAML::LoadFile(path)[map_key];
			bg_color = map_node["bg_color"].as<int>();
			layers = std::vector<TileLayer>();
			objects = std::vector<TileEntity>();
			layer_count = map_node["layers"]["count"].as<int>();
			for (int i = 0; i < layer_count; i++) {
				layers.push_back(TileLayer(map_node["layers"][i]));
				// std::cout << i << std::endl;
			}
			// std::cout << map_node["objects"] << std::endl;
			std::vector<String> object_names =
				map_node["objects"]["names"].as<std::vector<String>>();
			for (String name : object_names) {
				objects.push_back(*new TileEntity(
					map_node["objects"][name]["type"].as<String>(),
					map_node["objects"][name]["key"].as<String>(),
					map_node["objects"][name]["id"].as<int>(),
					map_node["objects"][name]["x"].as<int>(),
					map_node["objects"][name]["y"].as<int>()));
			}
		};
		std::vector<TileLayer> *get_layers();	/**< Getter for layers. */
		std::vector<TileEntity> *get_objects(); /**< Getter for objects. */
	};

}; // namespace mazengine

#endif // EBMAP_H_
