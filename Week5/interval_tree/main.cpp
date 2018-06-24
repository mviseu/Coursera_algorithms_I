#include "IntervalTree.h"

int main() {
	Interval i1(0, 3);
	Interval i2(1, 2);
	IntervalTree tree;
	tree.Insert(i1);
	tree.Insert(i2);
	tree.Delete(i1);
	tree.Delete(i2);
	return 0;
}