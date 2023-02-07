#include <tiles.h>

namespace mazengine {
	namespace tiles {
		Rect *Display::GetTileLocation(int x, int y) {
			(void)x;
			(void)y;
			return nullptr;
		}
		Rect *Display::GetTextureLocation(int tile_index) {
			(void)tile_index;

			int w = tileset_size[0] / tile_size[0];

			texture_location_rect.w = tile_size[0];
			texture_location_rect.h = tile_size[1];
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
