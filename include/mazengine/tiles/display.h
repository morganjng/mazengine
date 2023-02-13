#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "../element.h"
#include "../mazengine.h"
#include "../texture.h"
#include "tiles.h"
namespace mazengine {
	namespace tiles {
		class Entity;
		class EditorFollow;

		/**
		 * A Display is an Element that displays a map of tiles, following a
		 * certain Entity.
		 * */
		class Display : public Element {
		public:
			int status;
			Texture *tileset;
			int *tiles;
			Rect output;
			int *internal_size;
			int *tileset_size;
			int *tile_size;
			int *map_size;
			int *following_point;

			Rect tile_location_rect;
			Rect texture_location_rect;

			std::vector<std::string> triggers;

			Entity *following;
			std::vector<Entity> entities;
			std::string title;

			Display *Load(std::string title);
			void Save();

			Display *Tileset(std::string tileset_path);

			Display *Title(std::string title);
			Display *TileSize(int w, int h);
			Display *MapSize(int w, int h, int tile_preset);
			Display *TilesetSize(int w, int h);
			Display *InternalSize(int w, int h);
			Display *FollowingPoint(int x, int y);
			Display *Output(int x, int y, int w, int h);
			EditorFollow *Editor();

			Display() {
				triggers.clear();
				entities.clear();
				tile_size = (int *)malloc(sizeof(int) * 2);
				map_size = (int *)malloc(sizeof(int) * 2);
				tileset_size = (int *)malloc(sizeof(int) * 2);
				internal_size = (int *)malloc(sizeof(int) * 2);
				following_point = (int *)malloc(sizeof(int) * 2);
			}

			void SetTile(int x, int y, int val);
			/**
			 * Setup Rects for draw.
			 * */
			void ConfigureRects(int x, int y);
			int GetTile(int x, int y);
			int Tick();
			int Draw();
			std::pair<int, int> ScreenToWorld(int x, int y);
		};

	} // namespace tiles
} // namespace mazengine

#endif // DISPLAY_H_
