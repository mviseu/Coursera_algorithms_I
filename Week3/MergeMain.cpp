#include "Merge.h"
#include "MergeSort.h"
#include "BottomUpMergeSort.h"
#include <iterator>
#include <iostream>

void printVec(const std::vector<int>& v) {

	auto maxDisplayed = 100;
	for(const auto& elem : v) {
		std::cout << elem << ' ';
		if (--maxDisplayed == 0) {
			break;
		}
	}
	std::cout << std::endl;	
}

int main() {
	/*
	std::vector<int> vec = {6, 3, 8, 1, 7, 3, 9, 1, 42, 1000, 66, 33, 99, 98, 95, 1000};
	std::vector<int> mergedVec;
	Merge(vec.begin(), vec.begin() + 4, vec.begin() + 4, vec.end(), std::back_inserter(mergedVec));
	*/
	/*
	std::cout << "MERGE" << std::endl;
	for(const auto elem : mergedVec) {
		std::cout << elem << std::endl;
	}
	*/

	/*
	MergeSort(vec.begin(), vec.end());
	std::cout << "MERGESORT" << std::endl;
	for(const auto elem : vec) {
		std::cout << elem << std::endl;
	}*/


	std::vector<int> vecBottomUp = {};
	const auto bigNumber = 100000000;
	auto i = bigNumber;
	vecBottomUp.reserve(bigNumber);
	std::generate_n(std::back_inserter(vecBottomUp), bigNumber, [&i](){ return i--; });
	std::cout << "before:" << std::endl;
	printVec(vecBottomUp);
	BottomUpMergeSort(vecBottomUp.begin(), vecBottomUp.end());
	std::cout << "after:" << std::endl;
	printVec(vecBottomUp);

	return 0;
}

