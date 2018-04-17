#pragma once
#include <algorithm>
#include <iterator>
#include <iostream>

template <typename ForwardIterator, typename UnaryPredicate>
ForwardIterator Partition(ForwardIterator first, ForwardIterator last, UnaryPredicate p) {

	// Find first non-match
	auto rhs = first;
	while(rhs != last && p(*rhs)) {
		++rhs;
	}

	if(rhs == last) {
		return last;
	}


	// swap all the matches that are after rhs with non-matches that are at rhs 
	for(auto it = std::next(rhs); it != last; ++it) {
		if(p(*it)) {
			std::iter_swap(rhs, it);
			++rhs;
		}
	}
	return rhs;

}
