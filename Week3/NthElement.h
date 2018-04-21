#pragma once
#include "Partition.h"
#include <algorithm>
#include <functional>
#include <random>

template<typename RandomIt, typename Compare = std::less<typename RandomIt::value_type>>
void QuickSelect(RandomIt first, RandomIt nth, RandomIt last, Compare compare = Compare()) {
	if(first == last) {
		return;
	}
	const auto pivot = *first;
	const auto endNotLarger = Partition(first, last, [&pivot, &compare](const typename RandomIt::value_type& val) {
		return compare(val, pivot);
	});
	const auto beginNotSmaller = Partition(endNotLarger, last, [&pivot, &compare](const typename RandomIt::value_type& val) {
		return !compare(pivot, val);
	});

	if(nth < endNotLarger) {
		QuickSelect(first, nth, endNotLarger, compare);
	} else {
		if(nth > beginNotSmaller) {
			QuickSelect(beginNotSmaller, nth, last, compare);
		} else {
			return;
		}
	}
}

template <typename RandomIt, typename Compare = std::less<typename RandomIt::value_type>>
void NthElement(RandomIt first, RandomIt nth, RandomIt last, Compare compare = Compare()) {
// shuffle only first time (within partitions the subsets will also be shuffled if original was shuffled)
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(first, last, gen);

	QuickSelect<RandomIt>(first, nth, last, compare);
}