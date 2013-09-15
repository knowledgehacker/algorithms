#ifndef _POINT_H_
#define _POINT_H_

#include <ostream>

class Point {
private:
	int _x, _y;

public:
	Point(int x, int y);
	inline int getX()const {
		return _x;
	}
	inline int getY()const {
		return _y;
	}

	friend std::ostream& operator<<(std::ostream& os, const Point& point);

	~Point();
};

#endif
