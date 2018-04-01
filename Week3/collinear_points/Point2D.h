#pragma once
#include <string>

struct Point2D {
	Point2D() = default;
	Point2D(double xCoord, double yCoord);
	explicit operator std::string() const;
	double SlopeTo(const Point2D& rhs) const;
	double x{0.0};
	double y{0.0};
};

bool SlopeOrder(const Point2D& base, const Point2D& lhs, const Point2D& rhs);
bool operator==(const Point2D& lhs, const Point2D& rhs);
bool operator!=(const Point2D& lhs, const Point2D& rhs);
bool operator<(const Point2D& lhs, const Point2D& rhs);
bool operator>=(const Point2D& lhs, const Point2D& rhs);
bool operator>(const Point2D& lhs, const Point2D& rhs);
bool operator<=(const Point2D& lhs, const Point2D& rhs);

Point2D TranslateInBothAxis(const Point2D& point, double translateBy);
Point2D CompressByInBothAxis(const Point2D& point, double compressBy);