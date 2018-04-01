#pragma once
#include "Merge.h"
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>

template <typename RandomIt>
struct Range {
	Range(RandomIt start, RandomIt finish) : beg(start), end(finish) {}
	RandomIt beg = nullptr;
	RandomIt end = nullptr;
};

template<typename RandomIt> 
std::vector<Range<RandomIt>> CreateFirstRange(RandomIt beg, RandomIt end) {
	std::vector<Range<RandomIt>> oneElementRanges;
	auto it = beg;
	std::generate_n(std::back_inserter(oneElementRanges), std::distance(beg, end), [&it] () {
	    auto range = Range(it, it+1);
	    ++it;
	    return range; });
	return oneElementRanges;
}


template<typename RandomIt, typename Compare = std::less<typename RandomIt::value_type>>
void MergeAdjacentRanges(typename std::vector<Range<RandomIt>>::const_iterator rangeIt, Compare comp = Compare()) {
	std::vector<typename RandomIt::value_type> out;
	Merge(rangeIt->beg,rangeIt->end, (rangeIt + 1)->beg, (rangeIt + 1)->end, std::back_inserter(out), comp);
	std::copy(out.begin(), out.end(), rangeIt->beg);
}

template <typename RandomIt, typename Compare = std::less<typename RandomIt::value_type>>
std::vector<Range<RandomIt>> MergeAdjacentRanges(const std::vector<Range<RandomIt>>& ranges, Compare comp = Compare()) {
	std::vector<Range<RandomIt>> rangesMerged;
	for(auto rangeIt = ranges.cbegin(); rangeIt < ranges.cend(); rangeIt += 2) {
		if(rangeIt != ranges.cend() - 1) {
			MergeAdjacentRanges<RandomIt>(rangeIt, comp);
			rangesMerged.push_back(Range<RandomIt>(rangeIt->beg, (rangeIt+1)->end));
		} else {
			rangesMerged.push_back(Range<RandomIt>(rangeIt->beg, rangeIt->end));
		}
	}
	return rangesMerged;
}

template <typename RandomIt, typename Compare = std::less<typename RandomIt::value_type>>
void BottomUpMergeSort(RandomIt beg, RandomIt end, Compare comp = Compare()) {
	auto ranges = CreateFirstRange(beg, end);
	while(ranges.size() > 1) {
		ranges = MergeAdjacentRanges(ranges, comp);
	}
}


