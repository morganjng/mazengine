#ifndef ENTITY_H_
#define ENTITY_H_

#include "../geometry.h"
#include "../texture.h"
#include <map>

namespace mazengine {
	namespace tiles {
		/**
		 * An Entity is a movable and reacting element displayed in a Display
		 * object.
		 * */
		class Entity {
		public:
			int state;
			Rect location;
			Texture *texture;
			std::map<std::string, std::string> behaviors;
		};
	} // namespace tiles
} // namespace mazengine

#endif // ENTITY_H_
