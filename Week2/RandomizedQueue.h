#pragma once
#include "Vector.h"
#include <random>
#include <ctime>
#include <utility>

template<typename T>
class RandomizedQueue {
public:
RandomizedQueue() = default;
bool IsEmpty() const;
int Size() const;
void Enqueue(const T& item);
//T Dequeue();

private:
Vector<T> m_queue;
};


namespace {
int GetRandomInt(int minInclusive, int maxInclusive) {
	static std::default_random_engine e(std::time(nullptr));
	static std::uniform_int_distribution<int> ud(minInclusive, maxInclusive);
	return ud(e);
}


} // namespace

template<typename T>
bool RandomizedQueue<T>::IsEmpty() const {
	return m_queue.IsEmpty();
}

template<typename T>
int RandomizedQueue<T>::Size() const {
	return m_queue.Size();
}

template<typename T>
void RandomizedQueue<T>::Enqueue(const T& item) {
	m_queue.PushBack(item);
}

/*
template<typename T>
T RandomizedQueue<T>::Dequeue() {
	if(IsEmpty()) {
		std::runtime_error("Attempt to Dequeue an empty RandomizedQueue");
	}
	// select a random number between 0, size - 1
	auto maxIndex = Size() - 1;
	auto indexOfValToRemove = GetRandomInt(0, maxIndex);
	std::swap(m_queue[indexOfValToRemove], m_queue[maxIndex]);
	m_queue.PopBack(item);
}
*/
