#include <tiles.h>

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
		std::pair<int, int> Display::ScreenToWorld(int x, int y) {
			std::pair<int, int> a;
			if (!output.Contains(x, y)) {
				a.first = -1;
				a.second = -1;
				return a;
			}
			a.first = (following->location.x / tile_size[0]) -
				((output.x + output.w / 2) - x) /
					(tile_size[0] * output.w / internal_size[0]);
			a.second = (following->location.y / tile_size[1]) -
				((output.y + output.h / 2) - y) /
					(tile_size[1] * output.h / internal_size[1]);
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
