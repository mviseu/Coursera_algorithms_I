#include "NthElement.h"
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
	const std::vector<int> vecBase = {6, 3, 8, 1, 7, 3, 9, 1, 42, 1000, 66, 33, 99, 98, 95, 1000, 93, 2};
	auto sorted = vecBase;
	std::sort(sorted.begin(), sorted.end());
	auto vecMyAlgo = vecBase;
	NthElement(vecMyAlgo.begin(), vecMyAlgo.begin(), vecMyAlgo.end());
	std::cout << "min element is: " << vecMyAlgo.front() << std::endl;
	std::cout << "according to sort: " << sorted.front() << std::endl;
	vecMyAlgo = vecBase;
	NthElement(vecMyAlgo.begin(), vecMyAlgo.end() - 1, vecMyAlgo.end());
	std::cout << "max element is: " << vecMyAlgo.back() << std::endl;
	std::cout << "according to sort: " << sorted.back() << std::endl;
	vecMyAlgo = vecBase;
	NthElement(vecMyAlgo.begin(), vecMyAlgo.begin() + vecMyAlgo.size() / 2, vecMyAlgo.end());
	std::cout << "median element is: " << *(vecMyAlgo.begin() + vecMyAlgo.size() / 2) << std::endl;
	std::cout << "according to sort: " << *(sorted.begin() + sorted.size() / 2) << std::endl;

	return 0;
}

