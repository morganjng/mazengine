/*
 * UGame: A union of multiple other games, think a set of switching scenes
 */

#ifndef U_GAME_H_
#define U_GAME_H_

#include "mazengine.h"
#include <vector>

namespace mazengine {

	class UGame : public Game {
	private:
		std::vector<Game *> games;

	public:
		int cursor;
		int PushGame(Game *game);
		UGame(String _name) : Game(_name) { cursor = 0; };
		int InitialTick();
		int Tick(int status);
		int Draw();
		int Present();
		int React(int index);
	};

}; // namespace mazengine

#endif // U_GAME_H_
