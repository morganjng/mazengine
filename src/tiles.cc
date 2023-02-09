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
		Rect *Display::GetTileLocation(int x, int y) {
			tile_location_rect.w = tile_size[0] * (output.w / internal_size[0]);
			tile_location_rect.h = tile_size[1] * (output.h / internal_size[1]);

			int follow_point_x =
				following->location.x + (following->location.w / 2);
			int follow_point_y =
				following->location.y + (following->location.h / 2);

			int tl_x = -follow_point_x + internal_size[0] / 2;
			int tl_y = -follow_point_y + internal_size[1] / 2;

			int w_scale = output.w / internal_size[0];
			int h_scale = output.h / internal_size[1];

			tile_location_rect.x =
				((x * tile_size[0] + tl_x) * w_scale) + output.x;
			tile_location_rect.y =
				((y * tile_size[1] + tl_y) * h_scale) + output.y;

			if (tile_location_rect.x < output.x) {
				MoveSide(&tile_location_rect, 3, output.x);
			}

			if (tile_location_rect.y < output.y) {
				MoveSide(&tile_location_rect, 0, output.y);
			}

			if (tile_location_rect.x > output.x + output.w) {
				MoveSide(&tile_location_rect, 1, output.x + output.w);
			}

			if (tile_location_rect.y > output.y + output.h) {
				MoveSide(&tile_location_rect, 2, output.y + output.h);
			}

			return &tile_location_rect;
		}
		Rect *Display::GetTextureLocation(int tile_index) {
			int w = tileset_size[0] / tile_size[0];

			texture_location_rect.x = (tile_index % w) * tile_size[0];
			texture_location_rect.y = (tile_index / w) * tile_size[1];

			return &texture_location_rect;
		}
		int Display::GetTile(int x, int y) {
			return tiles[x + y * map_size[0]];
		}
		int Display::Tick() {
			following->location.x = *IO::cursor_x * Engine::window_width;
			following->location.y = *IO::cursor_y * Engine::window_height;
			std::cout << following->location.x << ", " << following->location.y
					  << std::endl;
			return 0;
		}
		int Display::Draw() {
			int off_x = following->location.x / tile_size[0];
			int off_y = following->location.y / tile_size[1];
			off_x = off_x - 1 - (internal_size[0] / tile_size[0] / 2);
			off_y = off_y - 1 - (internal_size[0] / tile_size[0] / 2);
			for (int i = 0; i < 2 + (internal_size[0] / tile_size[0]); i++) {
				for (int j = 0; j < 2 + (internal_size[1] / tile_size[1]);
					 j++) {
					if (i >= 0 && j >= 0 && i < map_size[0] &&
						j < map_size[0]) {
						tileset->Draw(GetTextureLocation(GetTile(i, j)),
									  GetTileLocation(i, j));
					}
				}
			}
			for (Entity entity : entities) {
			}
			return 0;
		}
	} // namespace tiles
} // namespace mazengine
