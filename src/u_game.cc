#include "mazengine.h"
#include <u_game.h>

using namespace mazengine;

int UGame::PushGame(Game *_game) {
	games.push_back(_game);
	return STATUS_OK;
}

int UGame::InitialTick() {
	if (name == "UNSET" || renderer == nullptr) {
		return UNSET_VALUE_ERROR;
	}

	int rv = STATUS_OK;
	for (int i = 0; i < int(games.size()); i++) {
		games[i]->renderer = renderer;
		games[i]->pass_pointers(presses, releases, cursor_x, cursor_y);
		rv = games[i]->InitialTick();
		if (rv != STATUS_OK) {
			return rv;
		}
	}
	return STATUS_OK;
}

int UGame::Tick(int status) {
	int rv = games[cursor]->Tick(cursor);
	if (rv != STATUS_OK) {
		return React(rv);
	}
	return STATUS_OK;
}

int UGame::Draw() { return games[cursor]->Draw(); }

int UGame::Present() { return games[cursor]->Present(); }

int UGame::React(int index) {
	if (index == ENGINE_KILL) {
		return ENGINE_KILL;
	}
	if (index > 0) {
		cursor = index - 1;
	}
	return STATUS_OK;
}
