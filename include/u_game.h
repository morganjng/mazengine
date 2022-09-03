#ifndef U_GAME_H_
#define U_GAME_H_

#include "mazengine.h"
#include <vector>

namespace mazengine {

	class u_game : public game {
	private:
		std::vector<game *> games;

	public:
		int cursor;
		int push_game(game *game);
		u_game() { renderer = nullptr; }
		int initial_tick();
		int tick();
		int draw();
		int present();
		int reaction(int index);
	};

}; // namespace mazengine

#endif // U_GAME_H_
