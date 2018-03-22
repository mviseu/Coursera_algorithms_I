#pragma once
#include "Merge.h"
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>


template <typename RandomIt>
void BottomUpMergeAuxiliary(RandomIt beg, RandomIt mid, RandomIt end) {
	std::vector<typename RandomIt::value_type> out;
	out.reserve(end - beg);
	Merge(beg, mid, mid, end, std::back_inserter(out));
	std::copy(out.cbegin(), out.cend(), beg);
}

template <typename RandomIt>
void BottomUpMergeSort(RandomIt beg, RandomIt end) {
	auto size = std::distance(beg, end);
	auto sz = 2;
	while(sz <= size) {
		for(auto it = beg; it < end; it += sz) {
			auto correctedSz = std::min(static_cast<long>(sz), std::distance(it, end));
			BottomUpMergeAuxiliary(it, it + (correctedSz + 1) / 2, it + correctedSz);
		}
		sz *= 2;
	}
	BottomUpMergeAuxiliary(beg, beg + sz / 2, end);
}
