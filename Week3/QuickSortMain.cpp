#include "Partition.h"
#include "QuickSort.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
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
	return vec;
}


int main() {
	const auto vecBase = CreateRandomVector(11);
	auto vec1 = vecBase;
	auto vec2 = vecBase;
	auto unaryPredicate = [](int i){return i > 3;};
	Partition(vec1.begin(), vec1.end(), unaryPredicate);
	std::partition(vec2.begin(), vec2.end(), unaryPredicate);

	std::cout << "My partition: ";
	Print(vec1);
	std::cout << std::endl;
	std::cout << "std::partition: "; 
	Print(vec2);
	std::cout << std::endl;

	QuickSort(vec1.begin(), vec1.end());
	std::cout << "My sort: ";
	Print(vec1);

	std::sort(vec2.begin(), vec2.end());

	std::cout << std::endl;
	std::cout << "std::sort: "; 
	Print(vec2);
	std::cout << std::endl;
	return 0;
}