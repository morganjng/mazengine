#include "mazengine.h"
#include <u_game.h>

using namespace mazengine;

int u_game::push_game(game *_game) {
	games.push_back(_game);
	return STATUS_OK;
}

int u_game::initial_tick() {
	if (name == "UNSET" || renderer == nullptr) {
		return UNSET_VALUE_ERROR;
	}

	int rv = STATUS_OK;
	for (int i = 0; i < int(games.size()); i++) {
		games[i]->renderer = renderer;
		games[i]->pass_pointers(presses, releases, cursor_x, cursor_y);
		rv = games[i]->initial_tick();
		if (rv != STATUS_OK) {
			return rv;
		}
	}
	return STATUS_OK;
}

int u_game::tick(int status) {
	int rv = games[cursor]->tick(cursor);
	if (rv != STATUS_OK) {
		return reaction(rv);
	}
	return STATUS_OK;
}

int u_game::draw() { return games[cursor]->draw(); }

int u_game::present() { return games[cursor]->present(); }

int u_game::reaction(int index) {
	if (index == ENGINE_KILL) {
		return ENGINE_KILL;
	}
	if (index > 0) {
		cursor = index - 1;
	}
	return STATUS_OK;
}
