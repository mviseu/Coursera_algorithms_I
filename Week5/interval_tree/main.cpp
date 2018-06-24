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
	Interval i1(0, 3);
	Interval i2(1, 2);
	Interval i4(-1, 2);
	Interval i3(2, 2);
	Interval i5(-2, 2);
	IntervalTree tree;
	tree.Insert(i1);
	tree.Insert(i2);
	tree.Insert(i3);
	tree.Insert(i4);
	tree.Insert(i5);

	ReportValueInTree(tree, i1);
	ReportValueInTree(tree, i2);
	ReportValueInTree(tree, i3);
	ReportValueInTree(tree, i4);
	ReportValueInTree(tree, i5);

	tree.Delete(i1);
	//tree.Delete(i2);
	//tree.Delete(i3);
	//tree.Delete(i4);
	//tree.Delete(i5);

	ReportValueInTree(tree, i1);
	ReportValueInTree(tree, i2);
	ReportValueInTree(tree, i3);
	ReportValueInTree(tree, i4);
	ReportValueInTree(tree, i5);
	return 0;
}