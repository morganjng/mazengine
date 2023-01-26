#ifndef MAZENGINE_GEOMETRY_H_
#define MAZENGINE_GEOMETRY_H_

namespace mazengine {
	/**
	 * The Point class is an abstraction away from the SDL point. To be used in
	 * polygons.
	 * */
	class Point {
	public:
		int x; /**< X-pos of the point. */
		int y; /**< Y-pos of the point. */
		/**
		 * Point contsructor. Direct analogue to initialization of SDL_Point.
		 * */
		Point(int x, int y) {
			this->x = x;
			this->y = y;
		}
	};

	/**
	 * Polygon class. To be done. Will eventually lead into a mesh for 3d
	 * objects.
	 * */
	class Polygon {};

	/**
	 * Abstraction of a rectangle away from the SDL implementation, so that the
	 * user will not have to interface with any SDL functionality directly.
	 * */
	class Rect : public Polygon {
	public:
		int x; /**< X-pos of the rectangle. */
		int y; /**< Y-pos of the rectangle. */
		int w; /**< Width of the rectangle.*/
		int h; /**< Height of the rectangle. */
		/**
		 * Rectangle contructor. Direct analogue to initialization of SDL_Rect.
		 * */
		Rect(int x, int y, int w, int h) {
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
		bool Contains(int x, int y);
	};
} // namespace mazengine

#endif // GEOMETRY_H_