#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "../element.h"
#include "../mazengine.h"
#include "../texture.h"
#include "tile.h"

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
			int status; /**< Current status. TODO remove magic numbers. */
			Texture
				*tileset; /**< Tileset being drawn from. TODO add sprites. */
			std::vector<std::vector<int>> tiles;	  /**< Tilemap in ints relating to tileset/eventually
							 sprites. */
			Rect output;  /**< Where to draw this on the window. */
			int *internal_size;	  /**< Native display size. */
			int *tileset_size;	  /**< in px. */
			int *tile_size;		  /**< in px. */
			int *map_size;		  /**< in tiles. */
			int *following_point; /**< in px of internal size. */

			/**
			 * Rect to be used in ConfigureRects.
			 * */
			Rect tile_location_rect;
			/**
			 * Rect to be used in ConfigureRects.
			 * */
			Rect texture_location_rect;

			/**
			 * Triggers to listen for. To be rethought soon.
			 * */
			std::vector<std::string> triggers;

			/**
			 * Entity that the "camera" follows. Center of this is placed at
			 * following_point.
			 * */
			Entity *following;
			/**
			 * All entities in this map.
			 * */
			std::vector<Entity> entities;
			/**
			 * Title of the map. Used to load in data.
			 * */
			std::string title;

			/**
			 * Load Display data from a given file.
			 * */
			Display *Load(std::string title);
			/**
			 * Save current data to respective file.
			 * */
			void Save();

			/**
			 * Load in Tileset at given path.
			 * */
			Display *Tileset(std::string tileset_path);

			Display *Title(std::string title);
			Display *TileSize(int w, int h);
			Display *MapSize(int w, int h, int tile_preset);
			Display *TilesetSize(int w, int h);
			Display *InternalSize(int w, int h);
			Display *FollowingPoint(int x, int y);
			Display *Output(int x, int y, int w, int h);

			/**
			 * Turn this display into an Editor.
			 * */
			EditorFollow *Editor();

			/**
			 * Display constructor. Allocates all pointers and clears vectors
			 * (just in case).
			 * */
			Display() {
				triggers.clear();
				entities.clear();
				tiles.clear();
				tile_size = (int *)malloc(sizeof(int) * 2);
				map_size = (int *)malloc(sizeof(int) * 2);
				tileset_size = (int *)malloc(sizeof(int) * 2);
				internal_size = (int *)malloc(sizeof(int) * 2);
				following_point = (int *)malloc(sizeof(int) * 2);
			}

			/**
			 * Change tile at (x, y) to val.
			 * */
			void SetTile(int x, int y, int val);
			/**
			 * Setup Rects for draw.
			 * */
			void ConfigureRects(int x, int y);
			/**
			 * Get Tile at (x, y). Soon int will be changed to a Tile object.
			 * */
			int GetTile(int x, int y);
			/**
			 * Increment game state.
			 * */
			int Tick();
			/**
			 * Draws visible tiles and entities to screen.
			 * */
			int Draw();
			/**
			 * Converts point on screen to the index of a point in the world.
			 * Returns (-1,-1) if out of bounds.
			 * */
			std::pair<int, int> ScreenToWorld(int x, int y);
		};

	} // namespace tiles
} // namespace mazengine

#endif // DISPLAY_H_
