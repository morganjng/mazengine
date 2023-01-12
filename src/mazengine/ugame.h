/*
 * UGame: A union of multiple other games, think a set of switching scenes
 */

#ifndef UGAME_H_
#define UGAME_H_

#include "mazengine.h"
#include <vector>

namespace mazengine {

	class UGame : public Game {
	protected:
		std::vector<Game *> games;

	public:
		int cursor;
		int PushGame(Game *game);
		UGame(String _name, Game *_parent) : Game(_name, _parent) {
			cursor = 0;
			games.clear();
		};
		int InitialTick();
		int Tick(int status);
		int Draw();
		int Present();
		int React(int index);
	};

}; // namespace mazengine

#endif // UGAME_H_
