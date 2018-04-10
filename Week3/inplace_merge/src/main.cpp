#include "InplaceMerge.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>

template<typename T>
void Print(const std::vector<T>& vec) {
	std::ostream_iterator<T> out(std::cout, " ");
	std::copy(vec.cbegin(), vec.cend(), out);
}

std::vector<int> CreateRandomVector(int size) {
	std::vector<int> vec(size);
	std::iota(vec.begin(), vec.end(), -size / 2);
    std::random_device rd;
    std::mt19937 g(rd());
	std::shuffle(vec.begin(), vec.end(), g);
	std::cout << "Base Vector" << std::endl;
	Print(vec);
	std::cout << std::endl;
	return vec;
}


int main() {
	const std::vector<int> vecUnmerged = CreateRandomVector(8);
	std::vector<int> vec = vecUnmerged;
	InplaceMerge(vec.begin(), vec.begin() + vec.size() / 2, vec.end());
	std::cout << "My Inplace Merge" << std::endl;
	Print(vec);
	std::cout << std::endl;

	std::cout << "std::inplace_merge" << std::endl;
	auto vecCopy = vecUnmerged;
	std::inplace_merge(vecCopy.begin(), vecCopy.begin() + vecCopy.size() / 2, vecCopy.end());
	Print(vecCopy);
	std::cout << std::endl;

	if(vec == vecCopy) {
		std::cout << "Congrats! Both vectors are equal!" << std::endl;
	} else {
		std::cout << "Sad... Revise code." << std::endl;
	}

	return 0;
}