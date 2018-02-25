#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>
#include "BinarySearch.h"

// If key in vector: returns true and the first iterator with that key in the vector
// If key not in vector: returns false and the first position after the key

std::pair<bool, std::vector<int>::const_iterator> BinarySearch(const std::vector<int>& sortedVec, int key) {
	auto top = sortedVec.end() - 1;
	auto bot = sortedVec.begin();
	auto mid = bot + (top - bot + 1) / 2;
	while(bot <= top) {
		if(*mid > key) {
			top = mid - 1;
		} else {
			if(*mid == key) {
				while(mid >= bot && *mid == *(mid -1)) {
					--mid;
				}
				return {true, mid};
			} else {
				bot = mid + 1;
			}
		}
		mid = bot + (top - bot + 1) / 2;
	}
	return {false, mid};
}