#pragma once
#include "BinaryHeap.h"
#include <functional>
#include <vector>
#include <stdexcept>

template <typename T, typename Compare = std::less<T>>
class PriorityQueue {
public:
	explicit PriorityQueue(const Compare& comp = Compare(), const std::vector<T>& vec = std::vector<T>({})) 
	: compare(comp), container(vec) {
		MakeHeap(container.begin(), container.end(), compare);
	}	

	bool Empty() const {return container.empty();}
	size_t Size() const {return container.size();}
	const T& Top() const {
		ThrowIfEmpty();
		return container.front();
	}
	void Push(const T& val) {
		container.push_back(val);
		PushHeap(container.begin(), container.end(), compare);
	}
	void Push(T&& val) {
		container.push_back(std::move(val));
		PushHeap(container.begin(), container.end(), compare);
	}
	void Pop() {
		ThrowIfEmpty();
		PopHeap(container.begin(), container.end(), compare);
		container.pop_back();
	}

private:
	void ThrowIfEmpty() const {
		if(container.empty()) {
			throw std::runtime_error("PriorityQueue is Empty.");
		}
	}
	Compare compare;
	std::vector<T> container;
};

/*
Add throw exception
*/
