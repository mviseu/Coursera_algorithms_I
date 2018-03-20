#pragma once
#include "Merge.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename RandomIt>
void MergeAuxiliary(RandomIt beg, RandomIt mid, RandomIt end) {
	std::vector<typename RandomIt::value_type> copy;
	copy.reserve(std::distance(beg, end));
	Merge(beg, mid, mid, end, std::back_inserter(copy));
	std::copy(copy.begin(), copy.end(), beg);
}

template <typename RandomIt>
void MergeSort(RandomIt beg, RandomIt end) {
	auto size = std::distance(beg, end);
	auto mid = beg + size / 2;
	if(size > 2) {
		MergeSort(beg, mid);
		MergeSort(mid, end);	
	}
	MergeAuxiliary(beg, mid, end);
}