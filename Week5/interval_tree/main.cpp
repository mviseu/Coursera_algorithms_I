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
	const Rectangle r4(Interval(6, 9), Interval(6, 9));
	const Rectangle r5(Interval(7, 8), Interval(7, 8));

	const Rectangle r6(Interval(10, 14), Interval(10, 11));
	const Rectangle r7(Interval(11, 15), Interval(12, 3));
	const Rectangle r8(Interval(12, 13), Interval(0, 20));	

	for(const auto& intersection : SweepLineRectangle({r1, r2, r3, r4, r5, r6, r7, r8})) {
		std::cout << "Intersections found for starting point x: " << intersection.x
				  << " and for Intervals: " << std::endl;
		PrintIntervals(intersection.yy);	
	}
	
	return 0;
}
