#pragma once
#include <functional>
#include <utility>

template <typename C, typename F = std::less<typename C::value_type>>
void ShellSort(typename C::iterator beg, typename C::iterator end, F compare = std::less<typename C::value_type>()) {
	auto size = end - beg;
	auto h = 0;
	while(h < size) {
		h = 3 * h + 1;
	}
	while(h >= 1) {
		for(auto it = beg; it + h < end; ++it) {
			for(auto itleft = it + h; itleft - h >= beg; itleft -= h) {
				if(compare(*itleft, *(itleft - h))) {
					using std::swap;
					swap(*itleft, *(itleft - h));
				} else {
					break;
				}
			}
		}
		h /= 3;
	}
}
