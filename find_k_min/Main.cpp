#include "Finder.h"

int main() {
	Point center(0, 0);
	Point points[] = {Point(1, 2), Point(2, 1), Point(3, 4),
		Point(-1, 1), Point(-3, 2), 
		Point(-1, 0), Point(-2, -2),
		Point(3, -1), Point(1, -3)
	};

	Finder finder(center, points, 4, sizeof(points)/sizeof(Point));
	finder.run();

	return 0;
}
