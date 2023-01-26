#include <geometry.h>
#include <ostream>

namespace mazengine {
	bool Rect::Contains(int x, int y) {
		return (this->x <= x && this->x + this->w >= x && this->y <= y &&
				this->y + this->h >= y);
	}

	Rect Rect::operator*(double mult) {
		this->x *= mult;
		this->y *= mult;
		this->w *= mult;
		this->h *= mult;
		return *this;
	}

	Rect Rect::operator*=(double mult) { return *this * mult; }

} // namespace mazengine
