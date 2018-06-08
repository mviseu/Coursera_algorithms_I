#include "OrthogonalLineSegment.h"
#include "SweepLine.h"
#include <iterator>
#include <iostream>

int main() {
	const auto a = OrthogonalLineSegment(Point(-5, 2), Point(-3, 2));
	const auto b = OrthogonalLineSegment(Point(-4, 4), Point(4, 4));
	const auto c = OrthogonalLineSegment(Point(-3, 0), Point(1, 0));
	const auto d = OrthogonalLineSegment(Point(-2, 3), Point(-2, -2));
	const auto e = OrthogonalLineSegment(Point(0, 5), Point(0, -3));
	const auto f = OrthogonalLineSegment(Point(1, 3), Point(3, 3));
	const auto intersections = SweepLine(std::vector<OrthogonalLineSegment>({a, b, c, d, e, f}));
	std::copy(intersections.begin(), intersections.end(), std::ostream_iterator<Point>(std::cout, "\n"));
	return 0;
}