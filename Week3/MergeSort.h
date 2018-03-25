#pragma once
#include "Merge.h"
#include "InsertionSort.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename RandomIt, typename Compare = std::less<typename RandomIt::value_type>>
void MergeAuxiliary(RandomIt beg, RandomIt mid, RandomIt end, Compare comp = Compare()) {
	std::vector<typename RandomIt::value_type> copy;
	copy.reserve(std::distance(beg, end));
	Merge(beg, mid, mid, end, std::back_inserter(copy), comp);
	std::copy(copy.begin(), copy.end(), beg);
}

template <typename RandomIt, typename Compare = std::less<typename RandomIt::value_type>>
void MergeSort(RandomIt beg, RandomIt end, Compare comp = Compare()) {
	auto size = std::distance(beg, end);
	if(size < 7) {
		InsertionSort(beg, end, comp);
	} else {
		auto mid = beg + size / 2;
		MergeSort(beg, mid, comp);
		MergeSort(mid, end, comp);
		if(comp(*mid, *(mid - 1))) {
			MergeAuxiliary(beg, mid, end, comp);
		}
	}
}