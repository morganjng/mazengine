#include <SDL2/SDL.h>
#include <geometry.h>
#include <iostream>
#include <mazengine.h>
#include <ostream>

namespace mazengine {
	int Point::Taxicab(int x1, int x2, int y1, int y2) {
		return (x1 - x2 < 0 ? x2 - x1 : x1 - x2) +
			(y1 - y2 < 0 ? y2 - y1 : y1 - y2);
	}

	int Point::SquareDistance(int x1, int x2, int y1, int y2) {
		return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
	}

	std::vector<Point> Polygon::GetPoints() { return this->points; }

	int Polygon::AddPoint(Point p) {
		this->points.push_back(p);
		return 0;
	}

	void Polygon::DrawPolygon(Polygon *polygon, char r, char g, char b,
							  char a) {
		std::vector<Point> points = polygon->GetPoints();

		SDL_Vertex *vertices =
			(SDL_Vertex *)malloc(sizeof(SDL_Vertex) * (points.size() + 1));
		for (size_t i = 0; i < points.size(); i++) {
			vertices[i].position.x = points[i].x;
			vertices[i].position.y = points[i].y;
			vertices[i].color.r = r;
			vertices[i].color.g = g;
			vertices[i].color.b = b;
			vertices[i].color.a = a;
		}

		vertices[points.size()].position.x = points[0].x + 1;
		vertices[points.size()].position.y = points[0].y;
		vertices[points.size()].color.r = r;
		vertices[points.size()].color.g = g;
		vertices[points.size()].color.b = b;
		vertices[points.size()].color.a = a;

		SDL_RenderGeometry(Engine::renderer, NULL, vertices, points.size(),
						   NULL, 0);
	}

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

	int Rect::AddPoint(Point p) { return 0; }

	void Rect::DrawBetween(Rect *rect1, Rect *rect2, char r, char g, char b,
						   char a) {
		std::vector<Point> points;
		for (int i = 0; i < 6; i++) {
			points.push_back(Point(0, 0));
		}
		int type;
		if (rect1->x < rect2->x && rect1->y < rect2->y) {
			type = 0;
		} else if (rect1->x > rect2->x && rect1->y < rect2->y) {
			type = 1;
		} else if (rect1->x < rect2->x && rect1->y > rect2->y) {
			type = 2;
		} else if (rect1->x > rect2->x && rect1->y > rect2->y) {
			type = 3;
		} else {
			type = 4;
		}
		std::cout << type << " -- ";
		switch (type) {
			case 0:
				points[0] = (Point(rect1->x, rect1->y));
				points[1] = (Point(rect1->x + rect1->w, rect1->y));
				points[2] = (Point(rect2->x + rect2->w, rect2->y));
				points[3] = (Point(rect2->x + rect2->w, rect2->y + rect2->h));
				points[4] = (Point(rect2->x, rect2->y + rect2->h));
				points[5] = (Point(rect1->x, rect1->y + rect1->h));
				break;
			case 1:
				points[0] = (Point(rect1->x, rect1->y));
				points[1] = (Point(rect1->x + rect1->w, rect1->y));
				points[2] = (Point(rect2->x + rect2->w, rect2->y));
				points[3] = (Point(rect2->x + rect2->w, rect2->y + rect2->h));
				points[4] = (Point(rect2->x, rect2->y + rect2->h));
				points[5] = (Point(rect1->x, rect1->y + rect1->h));
				break;
			case 2:
				points[0] = (Point(rect2->x, rect2->y));
				points[1] = (Point(rect2->x + rect2->w, rect2->y));
				points[2] = (Point(rect1->x + rect1->w, rect1->y));
				points[3] = (Point(rect1->x + rect1->w, rect1->y + rect1->h));
				points[4] = (Point(rect1->x, rect1->y + rect1->h));
				points[5] = (Point(rect2->x + rect2->w, rect2->y));
				break;
			case 3:
				points[0] = (Point(rect2->x, rect2->y));
				points[1] = (Point(rect2->x + rect2->w, rect2->y));
				points[2] = (Point(rect1->x + rect1->w, rect1->y));
				points[3] = (Point(rect1->x + rect1->w, rect1->y + rect1->h));
				points[4] = (Point(rect1->x, rect1->y + rect1->h));
				points[5] = (Point(rect2->x, rect2->y + rect2->h));
				break;
		}
		std::cout << std::endl;
		// points.push_back(Point(points[0].x + 1, points[0].y));
		std::cout << "Drawing polygon with points: ";
		for (auto x : points) {
			std::cout << "(" << x.x << ", " << x.y << "), ";
		}
		auto p = new Polygon(points);
		DrawPolygon(p, r, g, b, a);
		delete p;
	}

} // namespace mazengine
