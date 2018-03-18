#include "Point.h"

bool operator==(const Point& lhs, const Point& rhs) {
	return lhs.GetX() == rhs.GetX() && lhs.GetY() == rhs.GetY();
}

bool operator!=(const Point& lhs, const Point& rhs) {
	return !(lhs == rhs);
}

bool operator<(const Point& lhs, const Point& rhs) {
	if(lhs.GetX() < rhs.GetX()) {
		return true;
	}
	if(lhs.GetX() > rhs.GetX()) {
		return false;
	}
	// x coordinate is the same -> evaluate y coordinate
	if(lhs.GetY() < rhs.GetY()) {
		return true;
	}
	return false;	
}

bool operator<=(const Point& lhs, const Point& rhs) {
 return !(rhs < lhs);
}

bool operator>(const Point& lhs, const Point& rhs) {
	return rhs < lhs;
}

bool operator>=(const Point& lhs, const Point& rhs) {
	return !(lhs < rhs);
}