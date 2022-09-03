#include <u_game.h>

using namespace mazengine;

int u_game::initial_tick() {
	int rv = STATUS_OK;
	for (int i = 0; i < int(games.size()); i++) {
		rv = games[i]->initial_tick();
		if (rv != STATUS_OK) {
			return rv;
		}
	}
	return STATUS_OK;
}

int u_game::tick() {
	int rv = games[cursor]->tick();
	if (rv != STATUS_OK) {
		return reaction(rv);
	}
	return STATUS_OK;
}

int u_game::draw() { return games[cursor]->draw(); }

int u_game::present() { return games[cursor]->present(); }

int u_game::reaction(int index) { return STATUS_OK; }
