#pragma once
#include <string>

struct Point2D {
	Point2D() = default;
	Point2D(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}
	explicit operator std::string() const;
	int x{0};
	int y{0};
};

bool operator==(const Point2D& lhs, const Point2D& rhs);
bool operator!=(const Point2D& lhs, const Point2D& rhs);
bool operator<(const Point2D& lhs, const Point2D& rhs);
bool operator>=(const Point2D& lhs, const Point2D& rhs);
bool operator>(const Point2D& lhs, const Point2D& rhs);
bool operator<=(const Point2D& lhs, const Point2D& rhs);