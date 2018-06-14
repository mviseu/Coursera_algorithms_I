#include "KdTree.h"
#include <iostream>

void CheckIfPointInTree(const KdTree& tree, int (&point)[2]) {
	std::cout << "Search for point with x: " << point[0] << " and y: " << point[1] << std::endl;
	if(tree.Search(point)) {
		std::cout << "Point found" << std::endl;
	} else {
		std::cout << "Point not found" << std::endl;
	}
}

void ReportMin(const KdTree& tree) {
	if(const auto min = tree.FindMin()) {
		std::cout << "Minimum was found in tree. x is: "
				  << (*min)[0] << " and y is: "
				  << (*min)[1] << std::endl; 
	} else {
		std::cout << "Minimum does not exist." << std::endl;
	}
}

int main() {
	KdTree tree;
	int right[2] = {1, 0};
	int left[2] = {-1, 0};
	int up[2] = {0, 1};
	int down[2] = {0, -1};
	int outside[2] = {-2, 0};
	tree.Insert(right);
	tree.Insert(left);
	tree.Insert(up);
	tree.Insert(down);
	CheckIfPointInTree(tree, right);
	CheckIfPointInTree(tree, left);
	CheckIfPointInTree(tree, up);
	CheckIfPointInTree(tree, outside);
	CheckIfPointInTree(tree, down);
	ReportMin(tree);
	return 0;
}