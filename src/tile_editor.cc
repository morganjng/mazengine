#include <tiles/display.h>
#include <tiles/editor.h>

#include <io.h>

using namespace mazengine::tiles;

void EditorFollow::Move() {
	for (auto release : *IO::releases) {
		if (release == Button::SELECT) {
			if (state == 1) {
				state = 0;
				display->status = 254;
			} else {
				state = 1;
				display->status = 255;
			}
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
			if (state == 1) {
				display->status = 254;
				state = 0;
				int x_pos = *IO::cursor_x * Engine::window_width;
				int y_pos = *IO::cursor_y * Engine::window_height;
				int tile_w = display->tileset_size[0] / display->tile_size[0];
				int tile_h = display->tileset_size[1] / display->tile_size[1];
				tile_w = 960 / tile_w;
				tile_h = 720 / tile_h;
				int x = x_pos / tile_w;
				int y = y_pos / tile_h;
				current_brush =
					y * (display->tileset_size[0] / display->tile_size[0]) + x;
				clicked = 0;
				return;
			}
			clicked = 0;
		}
	}
	for (auto press : *IO::presses) {
		if (press == Button::MOUSE_CLICK) {
			if (state != 1) {
				clicked = 1;
				auto a = display->ScreenToWorld(
					*IO::cursor_x * Engine::window_width,
					*IO::cursor_y * Engine::window_height);
				display->SetTile(a.first, a.second, current_brush);
			}
		}
		if (press == Button::MOUSE_MOTION && clicked) {
			auto a =
				display->ScreenToWorld(*IO::cursor_x * Engine::window_width,
									   *IO::cursor_y * Engine::window_height);
			display->SetTile(a.first, a.second, current_brush);
		}
	}
}
