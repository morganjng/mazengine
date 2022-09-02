#ifndef U_GAME_H_
#define U_GAME_H_

#include "mazengine.h"
#include <vector>

using namespace mazengine;

class u_game : public game {
private:
	std::vector<game *> games;

public:
	int cursor;
	int push_game(game *game);
	u_game() { renderer = nullptr; }
	int initial_tick();
	int tick(std::vector<button> *presses, std::vector<button> *releases);
	int draw();
	int present();
	int reaction(int index);
};

#endif // U_GAME_H_
