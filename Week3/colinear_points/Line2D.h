#pragma once
#include "Point2D.h"

struct Line2D {
	Line2D(const Point2D& pPoint, const Point2D& qPoint) : p(pPoint), q(qPoint) {}
	Line2D() = default;
	Point2D p;
	Point2D q;
};