#pragma once
#include <string>

struct Point2D {
	Point2D() = default;
	Point2D(int xCoord, int yCoord);
	explicit operator std::string() const;
	double SlopeTo(const Point2D& rhs) const;
	int x{0};
	int y{0};
};

bool SlopeOrder(const Point2D& base, const Point2D& lhs, const Point2D& rhs);
bool operator==(const Point2D& lhs, const Point2D& rhs);
bool operator!=(const Point2D& lhs, const Point2D& rhs);
bool operator<(const Point2D& lhs, const Point2D& rhs);
bool operator>=(const Point2D& lhs, const Point2D& rhs);
bool operator>(const Point2D& lhs, const Point2D& rhs);
bool operator<=(const Point2D& lhs, const Point2D& rhs);