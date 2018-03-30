#pragma once
#include "Point2D.h"
#include <string>

struct Line2D {
	Line2D(const Point2D& pPoint, const Point2D& qPoint) : p(pPoint), q(qPoint) {}
	Line2D() = default;
	explicit operator std::string() const;
	Point2D p;
	Point2D q;
};