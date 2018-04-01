#include "Point2D.h"
#include <cassert>
#include <limits>
#include <iostream>
#include <sstream>


Point2D::Point2D(double xCoord, double yCoord) {
	x = xCoord;
	y = yCoord;	
}

Point2D::operator std::string() const {
	std::ostringstream os;
	os << "(" << x << ", " << y << ")";
	return os.str();
}

double Point2D::SlopeTo(const Point2D& rhs) const {
	if(*this == rhs) {
		return - std::numeric_limits<double>::infinity();
	}
	if(this-> x == rhs.x) {
		return std::numeric_limits<double>::infinity();
	}
	return (rhs.y - this->y) / (rhs.x - this->x);
}

bool SlopeOrder(const Point2D& base, const Point2D& lhs, const Point2D& rhs) {
	return base.SlopeTo(lhs) < base.SlopeTo(rhs);
}


bool operator==(const Point2D& lhs, const Point2D& rhs) {
	return lhs.y == rhs.y && lhs.x == rhs.x;
}

bool operator!=(const Point2D& lhs, const Point2D& rhs) {
	return !(lhs == rhs);
}

bool operator<(const Point2D& lhs, const Point2D& rhs) {
	return lhs.y < rhs.y || 
		   (lhs.y == rhs.y && lhs.x < rhs.x);
}

bool operator>=(const Point2D& lhs, const Point2D& rhs) {
	return !(lhs < rhs);
}

bool operator>(const Point2D& lhs, const Point2D& rhs) {
	return rhs < lhs;
}

bool operator<=(const Point2D& lhs, const Point2D& rhs) {
	return !(lhs > rhs);
}

Point2D TranslateInBothAxis(const Point2D& point, double translateBy) {
	return Point2D(point.x + translateBy, point.y + translateBy);
}

Point2D CompressByInBothAxis(const Point2D& point, double compressBy) {
	return Point2D(point.x / compressBy, point.y / compressBy);
}