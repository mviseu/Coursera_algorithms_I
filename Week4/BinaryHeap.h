#pragma once
#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
#include <cmath>

template <typename RandomIt, typename Compare = std::less<typename RandomIt::value_type>>
void PushHeap(RandomIt first, RandomIt last, Compare comp = Compare()) {
	if(first == last) {
		return;
	}
	auto child = last - 1;
	while(child != first) {
		const auto parent = std::distance(first, child - 1) / 2 + first;
		if(comp(*child, *parent)) {
			break;
		} else {
			std::iter_swap(child, parent);
			child = parent;
		}
	}
}

template <typename RandomIt, typename Compare = std::less<typename RandomIt::value_type>>
void PopHeap(RandomIt first, RandomIt last, Compare comp = Compare()) {
	if(first == last) {
		return;
	}
	const auto maxNewIt = std::prev(last);
	const int nrElementsWithoutMax = std::distance(first, maxNewIt);
	std::iter_swap(first, maxNewIt);
	auto parent = first;
	while(parent < first + nrElementsWithoutMax / 2) {
		const auto beforeChildren = first + 2 * std::distance(first, parent);
		auto child = std::next(beforeChildren);
		const auto secondChild = std::next(child);
		if(secondChild != maxNewIt && comp(*child, *secondChild)) {
			std::advance(child);
		}
		if(comp(*parent, *child)) {
			std::iter_swap(parent, child);
			parent = child;
		} else {
			break;
		}
	}
}



template <typename RandomIt, typename Compare = std::less<typename RandomIt::value_type>>
void MakeHeap(RandomIt first, RandomIt last, Compare comp = Compare()) {
	auto heapVec = std::vector<typename RandomIt::value_type>();
	for(auto it = first; it != last; ++it) {
		heapVec.push_back(*it);
		PushHeap(heapVec.begin(), heapVec.end(), comp);
	}
	std::copy(heapVec.begin(), heapVec.end(), first);
}