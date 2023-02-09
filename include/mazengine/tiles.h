#ifndef TILES_H_
#define TILES_H_

#include "element.h"
#include "geometry.h"
#include "mazengine.h"
#include "texture.h"

#include <vector>

namespace mazengine {
	namespace tiles {
		/**
		 * An Entity is a movable and reacting element displayed in a Display
		 * object.
		 * */
		class Entity {
		public:
			Rect location;
			Texture *texture;
		};

		/**
		 * A Display is an Element that displays a map of tiles, following a
		 * certain Entity.
		 * */
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

			Rect tile_location_rect;
			Rect texture_location_rect;

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

				auto map_size_temp = data["map_size"].as<std::vector<int>>();
				map_size = (int *)malloc(sizeof(int) * 2);
				map_size[0] = map_size_temp[0];
				map_size[1] = map_size_temp[1];

				auto tile_size_temp = data["tile_size"].as<std::vector<int>>();
				tile_size = (int *)malloc(sizeof(int) * 2);
				tile_size[0] = tile_size_temp[0];
				tile_size[1] = tile_size_temp[1];

				auto tileset_size_temp =
					data["tileset_size"].as<std::vector<int>>();
				tileset_size = (int *)malloc(sizeof(int) * 2);
				tileset_size[0] = tileset_size_temp[0];
				tileset_size[1] = tileset_size_temp[1];

				tiles = (int *)malloc(sizeof(int) * map_size[0] * map_size[1]);
				tileset = new Texture(data["tileset"].as<std::string>());

				auto temp = data["tiles"].as<std::vector<int>>();
				for (int i = 0; i < map_size[0] * map_size[1]; i++) {
					tiles[i] = temp[i];
				}

				texture_location_rect.w = tile_size[0];
				texture_location_rect.h = tile_size[1];

				tile_location_rect.w =
					tile_size[0] * (output.w / internal_size[0]);
				tile_location_rect.h =
					tile_size[1] * (output.h / internal_size[1]);

				following = new Entity;
				mazengine::Rect loc(16, 16, 0, 0);
				following->location = loc;
			}

			/**
			 * Return Rect describing where to draw this tile onto the window.
			 * */
			Rect *GetTileLocation(int x, int y);
			/**
			 * Return Rect describing where this tile exists on the tileset.
			 * */
			Rect *GetTextureLocation(int tile_index);
			int GetTile(int x, int y);
			int Tick();
			int Draw();
		};
	} // namespace tiles
} // namespace mazengine

#endif // TILE_DISPLAY_H_
