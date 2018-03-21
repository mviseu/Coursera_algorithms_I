#pragma once
#include "Merge.h"
#include <iterator>
#include <vector>

/*WIP
template <typename RandomIt>
void MergeAuxiliary(RandomIt it, int sz) {
	std::vector<typename RandomIt::value_type> out;
	auto midIt = it + sz / 2;
	auto endIt = it + sz;
	out.reserve(sz);
	Merge(it, midIt, midIt, endIt, std::back_inserter(out));
	std::copy(out.cbegin(), out.cend(), it);
}

template <typename RandomIt>
void BottomUpMergeSort(RandomIt beg, RandomIt end) {
	auto size = std::distance(beg, end);
	for(auto sz = 2; sz <= size / 2; sz *= 2) {
		for(auto it = beg; it <= end - sz; it += sz) {
			MergeAuxiliary(it, sz);
		}
	}
}
*/