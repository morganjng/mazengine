#ifndef ELEMENTS_H_
#define ELEMENTS_H_

#include "element.h"
#include "mazengine.h"

namespace mazengine {
	class Elements {
	public:
		static Element *Get(String key, Game *parent);
	};
} // namespace mazengine

#endif // ELEMENTS_H_
