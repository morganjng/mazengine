#ifndef MAZGAME_H_
#define MAZGAME_H_

#include "mazengine.h"
#include "mazobject.h"
#include <vector>

namespace mazengine {
	class Mazgame : public Game {
	private:
		std::vector<Mazobject *> objects;

	public:
		Mazgame(String _name) : Game(_name) { name = _name; }
		int InitialTick();
		int Tick(int status);
		int Draw();
		int Present();
		int React(int idx);
	};
} // namespace mazengine

#endif // MAZGAME_H_
