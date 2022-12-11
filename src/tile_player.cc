#include "mazengine/tile_player.h"

using namespace mazengine;

void tile_player::Tick(ButtonVector *presses, ButtonVector *releases) {
	for (Button press : *presses) {
		if (press < 4) {
			directions[press] = true;
		}
	}
	for (Button release : *releases) {
		if (release < 4) {
			directions[release] = false;
		}
	}

	for (int i = 0; i < 2; i++) {
		position_y += directions[i] * speed * (i * 2 - 1);
		if (directions[i]) {
			id = i;
		}
	}
	for (int i = 2; i < 4; i++) {
		position_x += directions[i] * speed * ((i - 2) * 2 - 1);
		if (directions[i]) {
			id = i;
		}
	}
}
