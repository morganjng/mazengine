#ifndef ELEMENT_H_
#define ELEMENT_H_

#include "mazengine.h"

namespace mazengine {
	/**
	 * Object that can be drawn on the screen and can be ticked.
	 * */
	class Element {
	public:
		/**
		 * Update state of Element.
		 * */
		virtual int Tick(int status) = 0;
		/**
		 * Draw Element on screen.
		 * */
		virtual int Draw() = 0;
	};
} // namespace mazengine

#endif // OBJECT_H_
