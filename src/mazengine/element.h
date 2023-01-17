#ifndef ELEMENT_H_
#define ELEMENT_H_

#include "mazengine.h"

namespace mazengine {
	class Element {
	public:
		virtual int Tick(int status) = 0;
		virtual int Draw() = 0;
	};
} // namespace mazengine

#endif // OBJECT_H_
