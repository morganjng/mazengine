#ifndef OBJECT_H_
#define OBJECT_H_

#include "mazengine.h"

namespace mazengine {
	class Object {
	protected:
		Game *parent;

	public:
		static Object *Get(String key, Game *parent);
		Object(Game *parent) { this->parent = parent; }
		int Tick(int status);
		int Draw();
	};
} // namespace mazengine

#endif // OBJECT_H_
