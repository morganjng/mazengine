/*
 * UGame: A union of multiple other games, think a set of switching scenes
 */

#ifndef UGAME_H_
#define UGAME_H_

#include "mazengine.h"
#include <vector>

namespace mazengine {
	/**
	 * Represents a union of Games which can switch between eachother.
	 * */
	class UGame : public Game {
	protected:
		std::vector<Game *> games; /**< Vector of games. */

	public:
		int cursor;				  /**< Current game being ticked/drawn. */
		int PushGame(Game *game); /**< Push game to vector. */
		/**
		 * UGame constructor. Default Game constructor with initializing cursor
		 * and games vector. Represents a union of Games which can switch
		 * between eachother.
		 * */
		UGame(String _name, Game *_parent) : Game(_name, _parent) {
			cursor = 0;
			games.clear();
		};
		int Tick(int status); /**< Tick current game. */
		int Draw();			  /**< Draw current game. */
		int Command(StringVector *command,
					size_t offset); /**< Command implementation. */
	};

}; // namespace mazengine

#endif // UGAME_H_
