#pragma once
#include <functional>
#include <algorithm>
#include <iostream>


template <typename InputIt1, typename InputIt2, typename OutputIt, typename Compare = std::less<typename InputIt1::value_type>>
OutputIt Merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt out, Compare compare = Compare()) {
	while(first1 != last1) {
		if(first2 == last2) {
			return std::copy(first1, last1, out);
		}
		if(compare(*first2, *first1)) {
			out = *first2++;
		} else {
			out = *first1++;
		}
	}
	return std::copy(first2, last2, out);
}