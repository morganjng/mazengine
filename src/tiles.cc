#include <tiles.h>

namespace mazengine {
	namespace tiles {
		Rect *Display::GetTileLocation(int x, int y) {
			int w_scale = output.w / internal_size[0];
			int h_scale = output.h / internal_size[1];

			tile_location_rect.x = (x * tile_size[0] * w_scale) -
				(following->location.x * w_scale) + output.x;
			tile_location_rect.y = (y * tile_size[1] * h_scale) -
				(following->location.y * h_scale) + output.y;

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
		int Display::Tick() { return 0; }
		int Display::Draw() { return 0; }
	} // namespace tiles
} // namespace mazengine
