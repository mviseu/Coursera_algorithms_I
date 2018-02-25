#include "BinarySearch.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>


using It = std::vector<int>::const_iterator;

namespace {
bool IsKeyInOrderedVec(const std::vector<int>& vec, int key) {
	auto ret = BinarySearch(vec, key);
	return ret.first;
}

int MidLength(std::vector<int>::const_iterator first, std::vector<int>::const_iterator last) {
	return (last - first + 1) / 2;
}

void ShiftToLeftSide(It max, const It old_beg, It beg, It old_end, It end) {
	end = max;
	old_end = end;
	max = beg;
	beg = old_beg;
}

void ShiftToRightSide(It max, It old_beg, It beg, const It old_end, It end) {
	beg = max;
	old_beg = beg;
	max = end;
	end = old_end;
}

} // namespace

// Returns first max in vector with bitonic order
std::vector<int>::const_iterator MaxInBitonic(const std::vector<int>& bitonicVec) {
	auto beg = bitonicVec.cbegin();
	auto end = bitonicVec.cend() - 1;
	auto max = beg + MidLength(beg, end);
	auto old_beg = beg;
	auto old_end = end;
	while(max > beg || max < end) {
		if(*max <= *beg) {
			ShiftToLeftSide(max, old_beg, beg, old_end, end);
		} else {
			if(*max < *end) {
				ShiftToRightSide(max, old_beg, beg, old_end, end);
			} else {
				beg = beg + MidLength(beg, max);
				end = end - MidLength(max, end);
			}
		}
	}
	return max;
}

// Checks if a given number is in a bitonic vector
bool IsKeyInBitonic(const std::vector<int>& bitonicVec, int key) {
	auto retBitonic = MaxInBitonic(bitonicVec);
	auto lowerVec = std::vector<int>(bitonicVec.cbegin(), retBitonic + 1);
	auto reverseRet = bitonicVec.crend() - (retBitonic - bitonicVec.cbegin());
	auto upperVec = std::vector<int>(bitonicVec.crbegin(), reverseRet);
	if(IsKeyInOrderedVec(lowerVec, key) || IsKeyInOrderedVec(upperVec, key)) {
		return true;
	}
	return false;
}



int main() {
	std::vector<int> vec = {1, 2, 3, 3, 5, 4, 4, 2};
	std::cout << *MaxInBitonic(vec) << std::endl;
	std::cout << IsKeyInBitonic(vec, 4) << std::endl;
	return 0;
}