#include "mazengine/ugame.h"
#include "mazengine/mazengine.h"

#include <iostream>

using namespace mazengine;

int UGame::PushGame(Game *_game) {
	games.push_back(_game);
	return STATUS_OK;
}

int UGame::Tick(int status) {
	int rv = games[cursor]->Tick(cursor);
	return rv;
}

int UGame::Draw() { return games[cursor]->Draw(); }

int UGame::Command(StringVector *command, size_t offset) {
	if (command->size() <= offset) {
		return 0;
	}
	if (command->at(offset) == "kill") {
		return ENGINE_KILL;
	}
	if (command->at(offset) == "game") {
		if (command->size() == 1) {
			return STATUS_OK;
		} else {
			cursor = std::stoi(command->at(offset + 1));
		}
	}
	return STATUS_OK;
}
