#include "Point.h"

Point::Point(int x, int y): _x(x), _y(y) {
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
	os<<"("<<point.getX()<<", "<<point.getY()<<")";

	return os;
}

Point::~Point() {
}
