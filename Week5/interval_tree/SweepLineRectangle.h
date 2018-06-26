#pragma once
#include "IntervalTree.h"
#include <queue>
#include <vector>

struct Rectangle {
	Rectangle(const Interval& x, const Interval& y) : xx(x), yy(y) {}
	Interval xx;
	Interval yy;
};

struct Intersection {
	Intersection(double xx, const std::vector<Interval>& yyy) : x(xx), yy(yyy) {}
	double x;
	std::vector<Interval> yy;
};

std::vector<Intersection> SweepLineRectangle(const std::vector<Rectangle>& rectangles);
