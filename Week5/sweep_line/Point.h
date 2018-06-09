#pragma once
#include <iostream>

struct Point {
	Point(double xx, double yy) : x(xx), y(yy) {}
	double x = 0;
	double y = 0;
};

std::ostream& operator<<(std::ostream& os, const Point& point);