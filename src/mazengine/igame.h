#ifndef IGAME_H_
#define IGAME_H_

#include "SDL_render.h"
#include "element.h"
#include "elements.h"
#include "mazengine.h"

#include <iostream>

namespace mazengine {
	class IGame : public Game {
	protected:
		std::vector<Element *> elements;
		std::vector<SDL_Texture *> backgrounds;

	public:
		int background_idx = -1;
		IGame(String _name, Game *_parent) : Game(_name, _parent) {}
		int InitialTick();
		int Tick(int status);
		int Draw();
		int Present();
		int React(int val);
	};
} // namespace mazengine

#endif // IGAME_H_
