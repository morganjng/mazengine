#ifndef IGAME_H_
#define IGAME_H_

#include "mazengine.h"
#include "object.h"

namespace mazengine {
	class IGame : public Game {
	protected:
		std::vector<Object *> objects;
		std::vector<SDL_Texture> background;
		int background_idx = -1;

	public:
		IGame(String _name) : Game(_name) {}
		int InitialTick();
		int Tick(int status);
		int Draw();
		int Present();
		int React(int val);
	};
} // namespace mazengine

#endif // IGAME_H_
