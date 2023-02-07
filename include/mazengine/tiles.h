#ifndef TILES_H_
#define TILES_H_

#include "element.h"
#include "geometry.h"
#include "mazengine.h"
#include "texture.h"

#include <vector>

namespace mazengine {
	namespace tiles {
		class Entity {};

		class Display : public Element {
		protected:
			Texture *tileset;
			Entity *following;
			std::vector<Entity> entities;
			int *tiles;
			Rect output;
			int *internal_size;
			int *tileset_size;
			int *tile_size;
			int *map_size;

		public:
			std::string title;
			Display(std::string title, Rect output) {
				this->output = output;
				this->title = title;
				auto data = YAML::LoadFile(
					(Engine::data_path + "tiles/" + title + ".yaml").c_str());

				internal_size = (int *)malloc(sizeof(int) * 2);
				internal_size[0] = data["width"].as<int>();
				internal_size[1] = data["height"].as<int>();

				map_size = data["map_size"].as<int *>();
				tile_size = data["tile_size"].as<int *>();
				tileset_size = data["tileset_size"].as<int *>();
				tiles = (int *)malloc(sizeof(int) * map_size[0] * map_size[1]);
				tileset = new Texture(data["tileset"].as<std::string>());

				auto temp = data["tiles"].as<std::vector<int>>();
				for (int i = 0; i < map_size[0] * map_size[1]; i++) {
					tiles[i] = temp[i];
				}
			}

			Rect *GetTileLocation(int tile_index);
			Rect *GetTextureLocation();
			int GetTile(int x, int y);
			int Tick();
			int Draw();
		};
	} // namespace tiles
} // namespace mazengine

#endif // TILE_DISPLAY_H_
