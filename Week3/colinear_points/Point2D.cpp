#include "Point2D.h"
#include <sstream>

Point2D::operator std::string() const {
	std::ostringstream os;
	os << "(" << x << ", " << y << ")";
	return os.str();
}

bool operator==(const Point2D& lhs, const Point2D& rhs) {
	return lhs.y == rhs.y && lhs.x == rhs.x;
}

bool operator!=(const Point2D& lhs, const Point2D& rhs) {
	return !(lhs == rhs);
}

bool operator<(const Point2D& lhs, const Point2D& rhs) {
	if(lhs.y < rhs.y) {
		return true;
	}
	return lhs.x < rhs.x;
}

bool operator>=(const Point2D& lhs, const Point2D& rhs) {
	return !(lhs < rhs);
}

bool operator>(const Point2D& lhs, const Point2D& rhs) {
	return rhs < lhs;
}

bool operator<=(const Point2D& lhs, const Point2D& rhs) {
	return !(rhs < lhs);
}