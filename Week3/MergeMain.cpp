#include "Merge.h"
#include "MergeSort.h"
#include <iterator>
#include <iostream>

int main() {
	std::vector<int> vec = {6, 3, 8, 1, 7, 3, 9, 1};
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


	std::cout << "TEST MERGE WITH 1 ELEMENT" << std::endl;
	std::vector<int> oneElem = {1};
	std::vector<int> mergedVec1Elem;
	Merge(oneElem.begin(), oneElem.end(), oneElem.end(), oneElem.end(), std::back_inserter(mergedVec1Elem));
	for(const auto elem : mergedVec1Elem) {
		std::cout << elem << std::endl;
	}
	return 0;
}

