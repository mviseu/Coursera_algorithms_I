#include "Merge.h"
#include <algorithm>
#include <ctime>
#include <forward_list>
#include <iostream>
#include <random>
#include <sstream>
#include <tuple>
#include <utility>

bool GetRandomBinaryInt() {
	static std::default_random_engine e(std::time(nullptr));
	std::bernoulli_distribution ud(0.5);
	return ud(e);
}

template <typename T>
typename std::forward_list<T>::iterator IncrementForwardIterator(typename std::forward_list<T>::iterator it, int nrTimes) {
	auto ret = it;
	for(auto i = 0; i != nrTimes; ++i) {
		++ret;
	}
	return ret;
}

template <typename T>
void RandomMerge(typename std::forward_list<T>::iterator itBegin,
				 typename std::forward_list<T>::iterator itMid,
				 typename std::forward_list<T>::iterator itEnd) {
	//for now vector, to be replaced by in-place merge
	std::vector<T> out;
	Merge(itBegin, itMid, itMid, itEnd, std::back_inserter(out), [](const T& lhs, const T& rhs) {return GetRandomBinaryInt();});
	std::copy(out.cbegin(), out.cend(), itBegin);
}

template<typename T>
int GetSize(typename std::forward_list<T>::iterator itBegin,
			typename std::forward_list<T>::iterator itEnd) {
	auto size = 0;
	for(auto it = itBegin; it != itEnd; ++it, ++size);
	return size;
}

template <typename T>
void ShuffleSinglyLinkedList(typename std::forward_list<T>::iterator itBegin,
							 typename std::forward_list<T>::iterator itEnd) {
	// O(N)
	auto size = GetSize<T>(itBegin, itEnd);
	const auto itMid = IncrementForwardIterator<T>(itBegin, size / 2);
	if(size > 1) {
		ShuffleSinglyLinkedList<T>(itBegin, itMid);
		ShuffleSinglyLinkedList<T>(itMid, itEnd);
	}
	RandomMerge<T>(itBegin, itMid, itEnd);
}

template <typename T>
void PrintSinglyLinkedList(const std::forward_list<T>& fwdList) {
	std::ostream_iterator<int> out(std::cout, "\n");
	std::copy(fwdList.cbegin(), fwdList.cend(), out);	
}

int main() {
	std::forward_list<int> someFwdList = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	ShuffleSinglyLinkedList<int>(someFwdList.begin(), someFwdList.end());
	PrintSinglyLinkedList(someFwdList);
	return 0;
}

