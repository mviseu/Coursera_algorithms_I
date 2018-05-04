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
void Sink(RandomIt first, RandomIt last, Compare comp = Compare()) {
	if(first == last) {
		return;
	}
	const auto nrElements = std::distance(first, last);
	auto parent = first;
	while(parent < first + nrElements / 2) {
		const auto beforeChildren = first + 2 * std::distance(first, parent);
		auto child = std::next(beforeChildren);
		const auto secondChild = std::next(child);
		if(secondChild != last && comp(*child, *secondChild)) {
			std::advance(child, 1);
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
void PopHeap(RandomIt first, RandomIt last, Compare comp = Compare()) {
	if(first == last) {
		return;
	}
	std::iter_swap(first, std::prev(last));
	Sink(first, std::prev(last), comp);
}


template <typename RandomIt, typename Compare = std::less<typename RandomIt::value_type>>
void MakeHeap(RandomIt first, RandomIt last, Compare comp = Compare()) {
	if(first == last) {
		return;
	}
	if(std::next(first) == last) {
		return;
	}
	auto treeNode = first + std::distance(first, last) / 2 - 1;
	while(treeNode >= first) {
		Sink(treeNode--, last, comp);
	}
}