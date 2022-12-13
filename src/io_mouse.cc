#include "mazengine/io_mouse.h"
#include "mazengine/mazengine.h"
#include <SDL_events.h>

using namespace mazengine;

int IOMouse::ReadSettings() { return 0; }

int IOMouse::Parse(SDL_Event *event) {
	if (event->type == SDL_QUIT) {
		presses->push_back(KILL);
		return ENGINE_KILL;
	}
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		presses->push_back(MOUSE_CLICK);
	}
	if (event->type == SDL_MOUSEMOTION) {
		presses->push_back(MOUSE_MOTION);
		*cursor_x = double(event->motion.x) / double(*window_width);
		*cursor_y = double(event->motion.y) / double(*window_height);
	}
	if (event->type == SDL_MOUSEBUTTONUP) {
		releases->push_back(MOUSE_CLICK);
	}
	return STATUS_OK;
}
