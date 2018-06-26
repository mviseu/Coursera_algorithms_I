#include "IntervalTree.h"
#include <iostream>

void ReportValueInTree(const IntervalTree& tree, const Interval& val) {
	if(tree.Find(val)) {
		std::cout << "Interval: " << val << " found." << std::endl;
	} else {
		std::cout << "Interval: " << val << " not found." << std::endl;
	}
}

int main() {
	Interval i1(17, 19);
	Interval i2(7, 10);
	Interval i4(15, 18);
	Interval i3(4, 8);
	Interval i5(21, 24);
	Interval i6(5, 8);
	IntervalTree tree;
	tree.Insert(i1);
	tree.Insert(i2);
	tree.Insert(i3);
	tree.Insert(i4);
	tree.Insert(i5);
	tree.Insert(i5);
	for(const auto& overlap : tree.AllOverlappingIntervals(Interval(9, 16))) {
		std::cout << "Interval " << overlap << " overlaps" << std::endl;
	}

	return 0;
}