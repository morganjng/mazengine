#include <tiles.h>

#include <fstream>
#include <iostream>

/**
 * Move side of a rectangle, changing width and height with it.
 *   * - 0 - *
 *   |       |
 *   3       1
 *   |       |
 *   * - 2 - *
 * */
void MoveSide(mazengine::Rect *rect, int side, int new_side) {
	switch (side) {
		case 0:
			rect->h = rect->h - (new_side - rect->y);
			rect->y = new_side;
			return;
		case 1:
			rect->w = new_side - rect->x;
			return;
		case 2:
			rect->h = new_side - rect->y;
			return;
		case 3:
			rect->w = rect->w - (new_side - rect->x);
			rect->x = new_side;
			return;
		default:
			return;
	}
}

namespace mazengine {
	namespace tiles {

		Display *Display::Load(std::string title) {
			this->title = title;
			auto data = YAML::LoadFile(
				(Engine::data_path + "tiles/" + title + ".yaml").c_str());

			internal_size[0] = data["width"].as<int>();
			internal_size[1] = data["height"].as<int>();

			auto map_size_temp = data["map_size"].as<std::vector<int>>();
			map_size[0] = map_size_temp[0];
			map_size[1] = map_size_temp[1];

			auto tile_size_temp = data["tile_size"].as<std::vector<int>>();
			tile_size[0] = tile_size_temp[0];
			tile_size[1] = tile_size_temp[1];

			auto tileset_size_temp =
				data["tileset_size"].as<std::vector<int>>();
			tileset_size[0] = tileset_size_temp[0];
			tileset_size[1] = tileset_size_temp[1];

			auto following_pt_temp =
				data["following_point"].as<std::vector<int>>();
			following_point[0] = following_pt_temp[0];
			following_point[1] = following_pt_temp[1];

			tiles = (int *)malloc(sizeof(int) * map_size[0] * map_size[1]);
			tileset = new Texture(data["tileset"].as<std::string>());

			auto temp = data["tiles"].as<std::vector<int>>();
			for (int i = 0; i < map_size[0] * map_size[1]; i++) {
				tiles[i] = temp[i];
			}

			return this;
		}

		void Display::Save() {
			std::ofstream fout;
			fout.open(Engine::data_path + "tiles/" + title + ".yaml");

			YAML::Emitter out;
			out.SetIndent(4);

			std::vector<int> temp;
			std::vector<std::string> temp_str;

			out << YAML::BeginMap;

			out << YAML::Key << "triggers";
			out << YAML::Value << triggers;

			out << YAML::Key << "width";
			out << YAML::Value << internal_size[0];

			out << YAML::Key << "height";
			out << YAML::Value << internal_size[1];

			out << YAML::Key << "tileset";
			out << YAML::Value << tileset->path;

			temp.clear();
			temp.push_back(map_size[0]);
			temp.push_back(map_size[1]);

			out << YAML::Key << "map_size";
			out << YAML::Value << temp;

			temp.clear();
			temp.push_back(tile_size[0]);
			temp.push_back(tile_size[1]);

			out << YAML::Key << "tile_size";
			out << YAML::Value << temp;

			temp.clear();
			temp.push_back(tileset_size[0]);
			temp.push_back(tileset_size[1]);

			out << YAML::Key << "tileset_size";
			out << YAML::Value << temp;

			temp.clear();
			temp.push_back(following_point[0]);
			temp.push_back(following_point[1]);

			out << YAML::Key << "following_point";
			out << YAML::Value << temp;

			temp.clear();

			for (int i = 0; i < map_size[0] * map_size[1]; i++) {
				temp.push_back(tiles[i]);
			}

			out << YAML::Key << "tiles";
			out << YAML::Value << temp;

			out << YAML::EndMap;

			fout << out.c_str();

			fout.close();
		}

		Display *Display::Tileset(std::string tileset_path) {
			tileset = new Texture(tileset_path);
			return this;
		}

		Display *Display::Title(std::string title) {
			this->title = title;
			return this;
		}

		Display *Display::TileSize(int w, int h) {
			tile_size[0] = w;
			tile_size[1] = h;
			return this;
		}
		Display *Display::MapSize(int w, int h, int tile_preset) {
			map_size[0] = w;
			map_size[1] = h;
			tiles = (int *)malloc(sizeof(int) * w * h);
			for (int i = 0; i < w * h; i++) {
				tiles[i] = tile_preset;
			}
			return this;
		}
		Display *Display::TilesetSize(int w, int h) {
			tileset_size[0] = w;
			tileset_size[1] = h;
			return this;
		}

		Display *Display::InternalSize(int w, int h) {
			internal_size[0] = w;
			internal_size[1] = h;
			return this;
		}

		Display *Display::FollowingPoint(int x, int y) {
			following_point[0] = x;
			following_point[1] = y;
			return this;
		}

		Display *Display::Output(int x, int y, int w, int h) {
			this->output.x = x;
			this->output.y = y;
			this->output.w = w;
			this->output.h = h;
			return this;
		}

		EditorFollow *Display::Editor() {
			triggers.push_back("onclick");
			triggers.push_back("onpress");

			auto e = new EditorFollow(tile_size[0], tile_size[1], map_size[0],
									  map_size[1], this);

			Engine::engine->main_namespace["editor"] =
				boost::python::object(*new EFWrapper(e));
			following = e;

			entities.push_back(*e);

			return e;
		};

		std::pair<int, int> Display::ScreenToWorld(int x, int y) {
			std::cout << "click at " << x << ", " << y;
			std::pair<int, int> a;
			if (!output.Contains(x, y)) {
				a.first = -1;
				a.second = -1;
				return a;
			}
			int w_scale = output.w / internal_size[0];
			int h_scale = output.h / internal_size[1];
			int _x = x - following_point[0] * w_scale +
				following->location.w / 2 + following->location.x * w_scale;
			int _y = y - following_point[1] * h_scale +
				following->location.h / 2 + following->location.y * h_scale;
			a.first = _x / (tile_size[0] * w_scale);
			a.second = _y / (tile_size[1] * h_scale);
			std::cout << "to " << a.first << ", " << a.second << std::endl;
			if (a.first < 0 || a.first > map_size[0]) {
				a.second = -1;
			}
			if (a.second < 0 || a.second > map_size[1]) {
				a.second = -1;
			}
			return a;
		}

		void Display::ConfigureRects(int x, int y) {
			int tile_index = GetTile(x, y);

			int w = tileset_size[0] / tile_size[0];

			texture_location_rect.x = (tile_index % w) * tile_size[0];
			texture_location_rect.y = (tile_index / w) * tile_size[1];

			texture_location_rect.w = tile_size[0];
			texture_location_rect.h = tile_size[1];

			tile_location_rect.w = tile_size[0] * (output.w / internal_size[0]);
			tile_location_rect.h = tile_size[1] * (output.h / internal_size[1]);

			int follow_point_x =
				following->location.x + (following->location.w / 2);
			int follow_point_y =
				following->location.y + (following->location.h / 2);

			int tl_x = -follow_point_x + following_point[0];
			int tl_y = -follow_point_y + following_point[1];

			int w_scale = output.w / internal_size[0];
			int h_scale = output.h / internal_size[1];

			tile_location_rect.x =
				((x * tile_size[0] + tl_x) * w_scale) + output.x;
			tile_location_rect.y =
				((y * tile_size[1] + tl_y) * h_scale) + output.y;

			if (tile_location_rect.x < output.x) {
				MoveSide(&texture_location_rect, 3,
						 ((output.x - tile_location_rect.x) / w_scale) +
							 texture_location_rect.x);
				MoveSide(&tile_location_rect, 3, output.x);
			}

			if (tile_location_rect.y < output.y) {
				MoveSide(&texture_location_rect, 0,
						 ((output.y - tile_location_rect.y) / h_scale) +
							 texture_location_rect.y);
				MoveSide(&tile_location_rect, 0, output.y);
			}

			if (tile_location_rect.x + tile_location_rect.w >
				output.x + output.w) {
				MoveSide(
					&texture_location_rect, 1,
					((output.x + output.w - tile_location_rect.x) / w_scale) +
						texture_location_rect.x);
				MoveSide(&tile_location_rect, 1, output.x + output.w);
			}

			if (tile_location_rect.y + tile_location_rect.h >
				output.y + output.h) {
				MoveSide(
					&texture_location_rect, 2,
					((output.y + output.h - tile_location_rect.y) / h_scale) +
						texture_location_rect.y);
				MoveSide(&tile_location_rect, 2, output.y + output.h);
			}
		}

		int Display::GetTile(int x, int y) {
			return tiles[x + y * map_size[0]];
		}

		int Display::Tick() {
			for (std::string trigger : triggers) {
				for (Entity e : entities) {
					Engine::Execute(e.behaviors[trigger]);
				}
			}
			return 0;
		}
		int Display::Draw() {
			int off_x = following_point[0] / tile_size[0];
			int off_y = following_point[1] / tile_size[1];
			off_x = off_x - 1 - (internal_size[0] / tile_size[0] / 2);
			off_y = off_y - 1 - (internal_size[0] / tile_size[0] / 2);
			for (int i = 0; i < 2 + (internal_size[0] / tile_size[0]); i++) {
				for (int j = 0; j < 2 + (internal_size[1] / tile_size[1]);
					 j++) {
					if (i >= 0 && j >= 0 && i < map_size[0] &&
						j < map_size[0]) {
						ConfigureRects(i, j);
						// std::cout << "x, y :" << i << ", " << j
						// 		  << "Rect : " << tile_location_rect.x << ", "
						// 		  << tile_location_rect.y << std::endl;
						tileset->Draw(&texture_location_rect,
									  &tile_location_rect);
					}
				}
			}
			for (Entity entity : entities) {
			}
			return 0;
		}

		void Display::SetTile(int x, int y, int val) {
			if (x == -1 || y == -1) {
				return;
			}
			tiles[x + y * map_size[0]] = val;
		}

		void EditorFollow::Move() {
			for (auto release : *IO::releases) {
				if (release == Button::SELECT) {
					std::cout << "Enter the new value for cursor." << std::endl;
					std::cin >> current_brush;
				}
				if (release == Button::START) {
					display->Save();
					Engine::engine->Stop();
				}
				if (release == Button::LEFT && location.x > 0) {
					location.x -= location.w;
				}
				if (release == Button::RIGHT) {
					location.x += location.w;
				}
				if (release == Button::UP && location.y > 0) {
					location.y -= location.h;
				}
				if (release == Button::DOWN) {
					location.y += location.h;
				}
			}
		}

		void EditorFollow::Paint() {
			for (auto release : *IO::releases) {
				if (release == Button::MOUSE_CLICK) {
					clicked = 0;
				}
			}
			for (auto press : *IO::presses) {
				if (press == Button::MOUSE_CLICK) {
					clicked = 1;
					auto a = display->ScreenToWorld(
						*IO::cursor_x * Engine::window_width,
						*IO::cursor_y * Engine::window_height);
					display->SetTile(a.first, a.second, current_brush);
				}
				if (press == Button::MOUSE_MOTION && clicked) {
					auto a = display->ScreenToWorld(
						*IO::cursor_x * Engine::window_width,
						*IO::cursor_y * Engine::window_height);
					display->SetTile(a.first, a.second, current_brush);
				}
			}
		}

	} // namespace tiles
} // namespace mazengine
