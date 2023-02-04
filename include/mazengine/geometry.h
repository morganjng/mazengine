#ifndef MAZENGINE_GEOMETRY_H_
#define MAZENGINE_GEOMETRY_H_

#include <ostream>
#include <vector>

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
		/**
		 * Calculate the distance-squared between two points.
		 * */
		static int SquareDistance(int x1, int x2, int y1, int y2);
		/**
		 * Calculate the taxicab-distance between two points.
		 * */
		static int Taxicab(int x1, int x2, int y1, int y2);
	};

	/**
	 * Polygon class. To be done. Will eventually lead into a mesh for 3d
	 * objects.
	 * */
	class Polygon {
	private:
		/**
		 * Vector of the points comprising this polygon. Can contain duplicates.
		 * */
		std::vector<Point> points;

	public:
		/**
		 * Empty constructor.
		 * */
		Polygon() {}
		/**
		 * Contstructor by providing vector of points.
		 * */
		Polygon(std::vector<Point> points) { this->points = points; }
		/**
		 * Returns a vector of the points in this polygon.
		 * */
		std::vector<Point> GetPoints();
		/**
		 * Add a point to the polygon.
		 * @return 0 if succeeds, other if fails
		 * */
		int AddPoint(Point p);
		/**
		 * Draws and fills a given Polygon in the RGBA color value provided.
		 * */
		static void DrawPolygon(Polygon *polygon, char r, char g, char b,
								char a);
	};

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
		 * Empty Rectangle initia/izer. Sets all values to 0.
		 * */
		Rect() {
			this->x = 0;
			this->y = 0;
			this->w = 0;
			this->h = 0;
		}
		/**
		 * Rectangle contructor. Direct analogue to initialization of SDL_Rect.
		 * */
		Rect(int x, int y, int w, int h) {
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
		/**
		 * Checks if the point (x,y) is contained within the Rectangle. Includes
		 * bounds.
		 * */
		bool Contains(int x, int y);
		/**
		 * Multiplying all values operator.
		 * */
		Rect operator*(double mult);
		/**
		 * Multiplication-assignment operator.
		 * */
		Rect operator*=(double mult);
		/**
		 * Declaring AddPoint so there are no errors here.
		 * */
		int AddPoint(Point p);
		/**
		 * Draw "between" 2 rects.
		 * */
		static void DrawBetween(Rect *rect1, Rect *rect2, char r, char g,
								char b, char a);
	};
} // namespace mazengine

#endif // GEOMETRY_H_
