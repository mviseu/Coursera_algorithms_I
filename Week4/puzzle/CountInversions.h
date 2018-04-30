#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

template <typename InputIt1, typename InputIt2, typename OutputIt>
int CountInterversionsWhileMerging(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt out) {
	auto inversions = 0;
	while(first1 != last1) {
		if(first2 == last2) {
			std::copy(first1, last1, out);
			return inversions;
		}
		if(*first2 < *first1) {
			out = *first2++;
			inversions += static_cast<int>(std::distance(first1, last1));
		} else {
			out = *first1++;
		}
	}
	std::copy(first2, last2, out);
	return inversions;
}

template <typename RandomIt>
int MergeInversion(RandomIt beg, RandomIt mid, RandomIt end) {
	std::vector<typename RandomIt::value_type> copy;
	copy.reserve(std::distance(beg, end));
	auto count = CountInterversionsWhileMerging(beg, mid, mid, end, std::back_inserter(copy));
	std::copy(copy.begin(), copy.end(), beg);
	return count;
}

template <typename RandomIt>
int CountInversionsAndMerge(RandomIt beg, RandomIt end) {
	auto size = std::distance(beg, end);
	auto inversions = 0;
	if(size <= 1) {
		return inversions;
	} else {
		auto mid = beg + size / 2;
		inversions += CountInversionsAndMerge(beg, mid);
		inversions += CountInversionsAndMerge(mid, end);
		return MergeInversion(beg, mid, end) + inversions;
	}
}

template <typename RandomIt>
int CountInversions(RandomIt beg, RandomIt end) {
	std::vector<RandomIt::value_type> saveCopy(beg, end);
	const auto ret = CountInversionsAndMerge(saveCopy.begin(), saveCopy.end());
	return ret;
}
