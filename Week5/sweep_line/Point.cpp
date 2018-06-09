#include "Point.h"

std::ostream& operator<<(std::ostream& os, const Point& point) {
	os << "x: " << point.x
	   << " y: " << point.y
	   << std::endl;
	return os;
}