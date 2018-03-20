#pragma once
#include <functional>
#include <algorithm>
#include <iostream>


template <typename InputIt1, typename InputIt2, typename OutputIt>
OutputIt Merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt out) {
	while(first1 != last1) {
		if(first2 == last2) {
			return std::copy(first1, last1, out);
		}
		if(*first1 < *first2) {
			out = *first1++;
		} else {
			out = *first2++;
		}
	}
	return std::copy(first2, last2, out);
}