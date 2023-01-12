/*
 * Header file for tile games
 */

#ifndef TILE_SET_H_
#define TILE_SET_H_

#include "mazengine.h"
#include "tile_layer.h"
#include <SDL2/SDL_render.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <string>
#include <yaml-cpp/yaml.h>

namespace mazengine {

	class TileSet {
	public:
		TileSet(String path, int w, int h, int size_x, int size_y) {
			texture = IMG_Load(path.c_str());
			width = w;
			height = h;
			tile_size_x = size_x;
			tile_size_y = size_y;
		}
		SDL_Surface *texture;
		int width;
		int height;
		int tile_size_x;
		int tile_size_y;
	};

	class TileRenderer {
	private:
		SDL_Surface *internal_surface;
		SDL_Renderer *renderer;
		SDL_Rect render_rect;
		StringVector tileset_names;
		std::map<String, TileSet *> tilesets;
		int tile_width;
		int tile_height;
		int tile_size_x;
		int tile_size_y;

	public:
		TileRenderer(SDL_Renderer *rend, String img_path, YAML::Node img_node,
					 int tile_width, int tile_height, int tile_size_x,
					 int tile_size_y) {
			this->tile_width = tile_width;
			this->tile_height = tile_height;
			this->tile_size_x = tile_size_x;
			this->tile_size_y = tile_size_y;
			renderer = rend;
			render_rect.x = 0;
			render_rect.y = 0;
			render_rect.w = tile_width * tile_size_x;
			render_rect.h = tile_height * tile_size_y;
			tilesets = std::map<String, TileSet *>();
			// std::cout << img_node << std::endl;
			tileset_names = img_node["names"].as<StringVector>();
			for (String name : tileset_names) {
				tilesets[name] =
					new TileSet(img_path + img_node[name]["path"].as<String>(),
								img_node[name]["width"].as<int>(),
								img_node[name]["height"].as<int>(),
								img_node[name]["tile_size_x"].as<int>(),
								img_node[name]["tile_size_y"].as<int>());
			}
			internal_surface = SDL_CreateRGBSurface(
				0, 4 * tile_size_x + tile_width * tile_size_x,
				4 * tile_size_y + tile_height * tile_size_y, 32, 0, 0, 0, 0);
		};
		void Clear(int color);
		void Draw_layer(TileLayer *layer, int offset_x, int offset_y);
		void DrawSprite(String key, int id, int x, int y);
		void Draw_to_renderer(int px_offset_x, int px_offset_y);
		void Present();
		// tile_set *get_tile_set(String key);
	};

}; // namespace mazengine

#endif // TILE_SET_H_