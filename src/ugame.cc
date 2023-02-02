#include <mazengine.h>
#include <ugame.h>

#include <iostream>

using namespace mazengine;

int UGame::PushGame(Game *_game) {
	games.push_back(_game);
	return STATUS_OK;
}

int UGame::Tick() {
	int rv = games[cursor]->Tick();
	return rv;
}

int UGame::Draw() { return games[cursor]->Draw(); }
