#include <u_game.h>

using namespace mazengine;

int u_game::initial_tick() {
	int rv = 0;
	for (int i = 0; i < int(games.size()); i++) {
		rv = games[i]->initial_tick();
		if (rv != 0) {
			return rv;
		}
	}
	return 0;
}

int u_game::tick(std::vector<button> *presses, std::vector<button> *releases) {
	int rv = games[cursor]->tick(presses, releases);
	if (rv != 0) {
		return reaction(rv);
	}
	return 0;
}

int u_game::draw() { return games[cursor]->draw(); }

int u_game::present() { return games[cursor]->present(); }

int u_game::reaction(int index) { return 0; }
