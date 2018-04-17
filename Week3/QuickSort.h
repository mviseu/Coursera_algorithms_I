#pragma once
#include <algorithm>
#include "Partition.h"
#include <functional>
#include <random>
#include <iostream>
#include <iterator>


template <typename ForwardIt, typename Compare = std::less<typename ForwardIt::value_type>>
void PartitionSort(ForwardIt first, ForwardIt last, Compare compare = Compare()) {
	if(first == last) {
		return;
	}
	const auto pivot = *first;
	const auto firstHalfEnd = Partition<ForwardIt>(first, last, 
						    [&pivot, &compare](const typename ForwardIt::value_type& val) {						    	
						    return compare(val, pivot);
						});

	// don't forget to separate equal elements from greater elements
	const auto secondHalfBegin = Partition<ForwardIt>(firstHalfEnd, last, 
						    [&pivot, &compare](const typename ForwardIt::value_type& val) {
						    return !compare(pivot, val);
						});
	PartitionSort(first, firstHalfEnd, compare);
	PartitionSort(secondHalfBegin, last, compare);
}

template <typename ForwardIt, typename Compare = std::less<typename ForwardIt::value_type>>
void QuickSort(ForwardIt first, ForwardIt last, Compare compare = Compare()) {

	// shuffle only first time (within partitions the subsets will also be shuffled if original was shuffled)
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(first, last, gen);

	PartitionSort(first, last, compare);

}