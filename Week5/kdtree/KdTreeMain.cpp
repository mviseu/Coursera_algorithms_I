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

void ReportDelete(int (&point)[2]) {
	std::cout << "Deleted point with x: " << point[0] << " and y: " << point[1] << std::endl;	
}

void DeleteEvent(KdTree& tree, int (&point)[2]) {
	CheckIfPointInTree(tree, point);
	tree.Delete(point);
	ReportDelete(point);
	CheckIfPointInTree(tree, point);
}

void ReportRangeSearch(int matches, int** res) {
	for(auto index = 0; index < matches; ++index) {
		std::cout << "Value with x: "  << res[index][0]
		<< " and y: " << res[index][1] << " was found in the range search"
		<< std::endl;
	}

}

void ReportClosestPoint(const KdTree& tree, const int (&target) [2]) {
	auto closestPoint = tree.ClosestPoint(target);
	std::cout << "Closest has x: " << closestPoint[0] << " and y: "
			  << closestPoint[1] << std::endl;
	delete [] closestPoint;
}

int main() {
	KdTree tree;
	//int extraOutside1[2] = {4, 2};
	int right[2] = {2, 0};
	int left[2] = {-2, 0};
	//int extraOutside2[2] = {-1, 3};
	int up[2] = {0, 2};
	int down[2] = {0, -2};
	int outside[2] = {-3, 3};
	//tree.Insert(extraOutside1);
	tree.Insert(right);
	tree.Insert(left);
	//tree.Insert(extraOutside2);
	tree.Insert(up);
	tree.Insert(down);
	tree.Insert(outside);
	CheckIfPointInTree(tree, right);
	CheckIfPointInTree(tree, left);
	CheckIfPointInTree(tree, up);
	CheckIfPointInTree(tree, outside);
	CheckIfPointInTree(tree, down);
	ReportMin(tree);

	/*
	DeleteEvent(tree, left);
	DeleteEvent(tree, right);
	DeleteEvent(tree, up);
	DeleteEvent(tree, down);
	*/
	/*
	int lowBound[2] = {-2, -2};
	int upBound[2] = {2, 2};
	const auto maxSize = 4000;
	int** container = new int*[maxSize];
	for(auto index = 0; index < maxSize; ++index) {
		container[index] = new int[2](); 
	}const KdTree& tree

	auto nrMatches = tree.SearchRange(&container[0], lowBound, upBound);
	std::cout << nrMatches << std::endl;
	ReportRangeSearch(nrMatches, &container[0]);
	for(auto index = 0; index < maxSize; ++index) {
		delete [] container[index]; 
	}
	delete [] container;
	*/
	int target[k] = {0, -1};
	ReportClosestPoint(tree, target);
	return 0;
}