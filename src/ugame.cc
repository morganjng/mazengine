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

int UGame::Command(StringVector *command) {
	for (unsigned i = 0; i < command->size(); i++) {
		std::cout << command->at(i) << ", ";
	}
	std::cout << std::endl;
	if (command->size() <= 0) {
		return 0;
	}
	if (command->at(0) == "kill") {
		return ENGINE_KILL;
	}
	if (command->at(0) == "game") {
		if (command->size() == 1) {
			return STATUS_OK;
		} else {
			cursor = std::stoi(command->at(1));
		}
	}
	return STATUS_OK;
}
