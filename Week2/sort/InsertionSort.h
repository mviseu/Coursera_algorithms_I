#pragma once
#include <functional>
#include <utility>

template <typename C, typename F = std::less<typename C::value_type>>
void InsertionSort(typename C::iterator beg, typename C::iterator end, F compare = std::less<typename C::value_type>()) {
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
