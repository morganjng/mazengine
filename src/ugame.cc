#include "mazengine/ugame.h"
#include "mazengine/mazengine.h"

#include <iostream>

using namespace mazengine;

int UGame::PushGame(Game *_game) {
	games.push_back(_game);
	return STATUS_OK;
}

int UGame::InitialTick() {
	int rv = STATUS_OK;
	for (int i = 0; i < int(games.size()); i++) {
		if (games[i] != nullptr) {
			std::cout << "Initializing game " << games[i]->name << std::endl;
			rv = games[i]->InitialTick();
		}
		if (rv != STATUS_OK) {
			std::cout << "Initializing game " << games[i]->name
					  << " failed with code " << rv << std::endl;
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
	games[cursor]->Tick(cursor);
	return STATUS_OK;
}
