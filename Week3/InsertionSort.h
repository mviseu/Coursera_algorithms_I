#pragma once
#include <functional>
#include <utility>

template <typename RandomIt, typename F = std::less<typename RandomIt::value_type>>
void InsertionSort(RandomIt beg, RandomIt end, F compare = F()) {
	for(auto it = beg; it < end; ++it) {
		for(auto itLeft = it; itLeft > beg; --itLeft) {
			if(compare(*itLeft, *(itLeft - 1))) {
				using std::swap;
				swap(*itLeft, *(itLeft - 1));
			} else {
				break;
			}
		}
	}	
}
