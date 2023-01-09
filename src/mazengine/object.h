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
		virtual int Tick(int status) = 0;
		virtual int Draw() = 0;
	};
} // namespace mazengine

#endif // OBJECT_H_
