#include "ShellSort.h"
#include "InsertionSort.h"
#include <vector>
#include <iostream>

int main() {
	std::vector<int> vec = {1, 7, 3, 2, 9, 4, 2, 7, 4};
	InsertionSort<std::vector<int>>(vec.begin(), vec.end());
	for(const auto& elem: vec) {
		std::cout << elem << std::endl;
	}

	InsertionSort<std::vector<int>>(vec.begin(), vec.end(), [](int a, int b) {return a > b;});
	for(const auto& elem: vec) {
		std::cout << elem << std::endl;
	}

	std::cout << "ShellSort" << std::endl;
	std::vector<int> shellVec = {1, 7, 3, 2, 9, 4, 2, 7, 4, 0, 40, 6, 8, 1000, 1, -1, -50, 1, 7, 3, 2, 9, 4, 2, 7, 4, 0, 40, 6, 8, 1000, 1, -1, -50};
	ShellSort<std::vector<int>>(shellVec.begin(), shellVec.end());
	for(const auto& elem: shellVec) {
		std::cout << elem << std::endl;
	}

	return 0;
}