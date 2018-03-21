#include "Merge.h"
#include "MergeSort.h"
#include "BottomUpMergeSort.h"
#include <iterator>
#include <iostream>

int main() {
	std::vector<int> vec = {6, 3, 8, 1, 7, 3, 9, 1, 42, 1000, 66, 33, 99, 98, 95, 1000};
	std::vector<int> mergedVec;
	Merge(vec.begin(), vec.begin() + 4, vec.begin() + 4, vec.end(), std::back_inserter(mergedVec));

	std::cout << "MERGE" << std::endl;
	for(const auto elem : mergedVec) {
		std::cout << elem << std::endl;
	}

	MergeSort(vec.begin(), vec.end());
	std::cout << "MERGESORT" << std::endl;
	for(const auto elem : vec) {
		std::cout << elem << std::endl;
	}

/*
	std::vector<int> vecBottomUp = {6, 3, 8, 1, 7, 3, 9, 1, 42, 1000, 66, 33, 99, 98, 97};
	BottomUpMergeSort(vecBottomUp.begin(), vecBottomUp.end());
	std::cout << "BOTTOM UP MERGE SORT" << std::endl;
	for(const auto& elem : vecBottomUp) {
		std::cout << elem << std::endl;
	}
*/
	return 0;
}

