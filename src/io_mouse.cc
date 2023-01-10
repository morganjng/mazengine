#include "mazengine/io_mouse.h"
#include "mazengine/mazengine.h"
#include <SDL_events.h>

using namespace mazengine;

int IOMouse::ReadSettings() { return 0; }

int IOMouse::Parse(SDL_Event *event) {
	if (event->type == SDL_QUIT) {
		IO::presses->push_back(KILL);
		return ENGINE_KILL;
	}
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		IO::presses->push_back(MOUSE_CLICK);
	}
	if (event->type == SDL_MOUSEMOTION) {
		IO::presses->push_back(MOUSE_MOTION);
		*IO::cursor_x = double(event->motion.x) / double(*window_width);
		*IO::cursor_y = double(event->motion.y) / double(*window_height);
	}
	if (event->type == SDL_MOUSEBUTTONUP) {
		IO::releases->push_back(MOUSE_CLICK);
	}
	return STATUS_OK;
}
