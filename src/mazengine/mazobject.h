#ifndef MAZOBJECT_H_
#define MAZOBJECT_H_

#include "mazengine.h"

namespace mazengine {
	class Mazobject {
	public:
		static Mazobject *Get(String id);
		int Tick(int status);
		int Draw(SDL_Renderer *renderer);
	};
} // namespace mazengine
#endif // MAZOBJECT_H_
