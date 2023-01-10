#ifndef ELEMENT_H_
#define ELEMENT_H_

#include "mazengine.h"

namespace mazengine {
	class Element {
	protected:
		Game *parent;

	public:
		Element(Game *parent) { this->parent = parent; }
		virtual int Tick(int status) = 0;
		virtual int Draw() = 0;
	};
} // namespace mazengine

#endif // OBJECT_H_
