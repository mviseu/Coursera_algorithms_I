#include "IntervalTree.h"
#include "SweepLineRectangle.h"
#include <algorithm>
#include <iostream>
#include <iterator>

void ReportValueInTree(const IntervalTree& tree, const Interval& val) {
	if(tree.Find(val)) {
		std::cout << "Interval: " << val << " found." << std::endl;
	} else {
		std::cout << "Interval: " << val << " not found." << std::endl;
	}
}

void PrintIntervals(const std::vector<Interval>& intervals) {
	std::ostream_iterator<Interval> os(std::cout, "\n");
	std::copy(intervals.cbegin(), intervals.cend(), os);
}

int main() {
	const Rectangle r1(Interval(-3, 3), Interval(0, 2));
	const Rectangle r2(Interval(-2, -1), Interval(0, 1));
	const Rectangle r3(Interval(2, 3), Interval(4, 5));
	for(const auto& intersection : SweepLineRectangle({r1, r2, r3})) {
		std::cout << "Intersections found for starting point x: " << intersection.x
				  << " and for Intervals: " << std::endl;
		PrintIntervals(intersection.yy);	
	}
	return 0;
}

/*
Examples to be included

CASE 1
Rectangle1: xx: -3, 3, y: 0 2

Intersects:
xx: -2, -1 yy: 0 , 1

Does not intersect:
xx
2, 3 yy: 4, 5

Expected: 1 intersection with x = -2 and y between 0, 2


*/
