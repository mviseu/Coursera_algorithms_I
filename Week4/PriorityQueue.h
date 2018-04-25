#pragma once
#include "BinaryHeap.h"
#include <functional>
#include <vector>

template <typename T, typename Compare = std::less<T>>
class PriorityQueue {
public:
	explicit PriorityQueue(const Compare& comp = Compare(), const std::vector<T>& vec = std::vector<T>({})) 
	: compare(comp), container(vec) {
		MakeHeap(container.begin(), container.end(), compare);
	}	

	bool Empty() const {return container.empty();}
	int Size() const {return container.size();}
	const T& Top() const {return container.front();}
	void Push(const T& val) {
		container.push_back(val);
		PushHeap(container.begin(), container.end(), compare);
	}
	void Push(T&& val) {
		container.push_back(std::move(val));
		PushHeap(container.begin(), container.end(), compare);
	}
	void Pop() {
		PopHeap(container.begin(), container.end(), compare);
		container.pop_back();
	}

private:
	Compare compare;
	std::vector<T> container;
};