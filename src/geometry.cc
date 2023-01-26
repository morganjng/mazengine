#include <geometry.h>

namespace mazengine {
	bool Rect::Contains(int x, int y) {
		return (this->x <= x && this->x + this->w >= x && this->y <= y &&
				this->y + this->h >= y);
	}

} // namespace mazengine
