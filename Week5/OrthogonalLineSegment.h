#pragma once
#include "Point.h"
#include <cassert>

struct OrthogonalLineSegment;
bool IsLineHorizontal(const OrthogonalLineSegment& line);
bool IsLineVertical(const OrthogonalLineSegment& line);

struct OrthogonalLineSegment {
	OrthogonalLineSegment(const Point& pt1, const Point& pt2) : start(pt1), end(pt2) {
		assert(IsLineHorizontal(*this) || IsLineVertical(*this));
	}
	Point start;
	Point end;
};