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
		protected:
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

		public:
			Entity *following;
			std::vector<Entity> entities;
			std::string title;

			Display(std::string title) {
				this->output = Rect(0, 0, 960, 720);
				this->title = title;
				auto data = YAML::LoadFile(
					(Engine::data_path + "tiles/" + title + ".yaml").c_str());

				triggers.clear();
				triggers.push_back("onclick");
				triggers.push_back("onpress");

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

				auto following_pt_temp =
					data["following_point"].as<std::vector<int>>();
				following_point = (int *)malloc(sizeof(int) * 2);
				following_point[0] = following_pt_temp[0];
				following_point[1] = following_pt_temp[1];

				tiles = (int *)malloc(sizeof(int) * map_size[0] * map_size[1]);
				tileset = new Texture(data["tileset"].as<std::string>());

				auto temp = data["tiles"].as<std::vector<int>>();
				for (int i = 0; i < map_size[0] * map_size[1]; i++) {
					tiles[i] = temp[i];
				}

				auto e = new EditorFollow(tile_size[0], tile_size[1],
										  map_size[0], map_size[1], this);
				Engine::engine->main_namespace["editor"] =
					boost::python::object(EFWrapper(e));
				following = e;

				entities.push_back(*following);
			}

			Display(std::string title, std::string tileset, int tileset_w,
					int tileset_h, int internal_w, int internal_h, int tile_w,
					int tile_h, int map_w, int map_h, int following_x,
					int following_y, Rect output) {
				this->title = title;
				this->output = output;
				this->tileset = new Texture(tileset);

				// Triggers for editing, empty vector is written to file
				triggers.clear();
				triggers.push_back("onclick");
				triggers.push_back("onpress");

				tiles = (int *)malloc(sizeof(int) * map_h * map_w);

				for (int i = 0; i < map_w * map_h; i++) {
					tiles[i] = 0;
				}

				tile_size = (int *)malloc(sizeof(int) * 2);
				map_size = (int *)malloc(sizeof(int) * 2);
				tileset_size = (int *)malloc(sizeof(int) * 2);
				internal_size = (int *)malloc(sizeof(int) * 2);
				following_point = (int *)malloc(sizeof(int) * 2);

				tile_size[0] = tile_w;
				tile_size[1] = tile_h;
				tileset_size[0] = tileset_w;
				tileset_size[1] = tileset_h;
				map_size[0] = map_w;
				map_size[1] = map_h;
				internal_size[0] = internal_w;
				internal_size[1] = internal_h;
				following_point[0] = following_x;
				following_point[1] = following_y;

				auto e = new EditorFollow(tile_w, tile_h, map_w, map_h, this);
				Engine::engine->main_namespace["editor"] =
					boost::python::object(EFWrapper(e));
				following = e;

				entities.push_back(*following);
			}

			Display(std::string title, Rect output) {
				this->output = output;
				this->title = title;
				auto data = YAML::LoadFile(
					(Engine::data_path + "tiles/" + title + ".yaml").c_str());

				triggers = data["triggers"].as<std::vector<std::string>>();

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

				following = new Entity;
				mazengine::Rect loc(16, 16, 0, 0);
				following->location = loc;
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

		class Sidebar : public Element {
		public:
			Display *display;
			Texture *texture;
			Sidebar(Display *display) { this->display = display; };
		};
	} // namespace tiles
} // namespace mazengine

#endif // TILE_DISPLAY_H_
