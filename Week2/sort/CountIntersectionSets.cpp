#include "ShellSort.h"
#include "Point.h"
#include <vector>
#include <iostream>

int SortAndCountIntersection(std::vector<Point>& vecA, std::vector<Point>& vecB) {
	ShellSort<std::vector<Point>>(vecA.begin(), vecA.end());
	ShellSort<std::vector<Point>>(vecB.begin(), vecB.end());
	int count{0};
	for(auto itA = vecA.cbegin(), itB = vecB.cbegin(); itA < vecA.cend(); ++itA) {
		while(!(*itB > *itA)) {
			if(*itB == *itA) {
				++count;
			}
			++itB;
		}
	}
	return count;
}

int main() {
	std::vector<Point> vecA = {{0, 1}, {0, 2}, {0, -1}, {0, 1}, {1, 1}, {-1, 1}, {42, 1}, {42, 2}, {42, -1}, {42, 5}, {1000, 5}, {-1000, 5}};
	std::vector<Point> vecB = {{0, 1}, {1, 2}, {0, -1}, {0, 1}, {1, 1}, {-1, 1}, {42, 1}, {42, 2}, {42, -1}, {42, 5}, {1000, 5}, {-1001, 5}};
	std::cout << SortAndCountIntersection(vecA, vecB) << std::endl;

	return 0;
}