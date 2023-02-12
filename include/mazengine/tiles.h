#ifndef TILES_H_
#define TILES_H_

#include "element.h"
#include "geometry.h"
#include "mazengine.h"
#include "texture.h"

#include <vector>

namespace mazengine {
	namespace tiles {
		class Display;
		/**
		 * An Entity is a movable and reacting element displayed in a Display
		 * object.
		 * */
		class Entity {
		public:
			int state;
			Rect location;
			Texture *texture;
			std::map<std::string, std::string> behaviors;
		};

		class EditorFollow : public Entity {
		public:
			int **tiles_ptr;
			int map_w;
			int map_h;
			int clicked;
			int current_brush;
			Display *display;
			EditorFollow(int tile_w, int tile_h, int map_w, int map_h,
						 Display *display)
				: Entity() {
				current_brush = 1;
				this->location.x = 0;
				this->location.y = 0;
				this->map_w = map_w;
				this->map_h = map_h;
				this->location.w = tile_w;
				this->location.h = tile_h;
				this->display = display;
				clicked = 0;
				behaviors["onclick"] = "editor.Paint()\n";
				behaviors["onpress"] = "editor.Move()\n";
			}
			void Move();
			void Paint();
		};

		class EFWrapper {
		public:
			mazengine::tiles::EditorFollow *ef;
			EFWrapper(mazengine::tiles::EditorFollow *ef) { this->ef = ef; }
			void Paint() { ef->Paint(); }
			void Move() { ef->Move(); }
		};

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

#endif // TILE_DISPLAY_H_
