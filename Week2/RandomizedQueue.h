#pragma once
#include "RandomIntGenerator.h"
#include "RandomizedQueueNext.h"
#include "Vector.h"
#include <stdexcept>
#include <iostream>
#include <memory>
#include <functional>

template <typename T> class RandomizedQueueNext;

template<typename T>
class RandomizedQueue {
public:
RandomizedQueue();
bool IsEmpty() const;
int Size() const;
void Enqueue(const T& item);
T Dequeue();
T Sample();
RandomizedQueueNext<T> CreateNext() const;

private:
int MaxIndex() const;
std::shared_ptr<Vector<T>> m_queue;
};

template<typename T>
RandomizedQueue<T>::RandomizedQueue() {
	m_queue = std::make_shared<Vector<T>>();
}

template<typename T>
bool RandomizedQueue<T>::IsEmpty() const {
	return m_queue->IsEmpty();
}

template<typename T>
int RandomizedQueue<T>::Size() const {
	return m_queue->Size();
}

template<typename T>
int RandomizedQueue<T>::MaxIndex() const {
	return Size() - 1;
}

template<typename T>
void RandomizedQueue<T>::Enqueue(const T& item) {
	m_queue->PushBack(item);
}


template<typename T>
T RandomizedQueue<T>::Dequeue() {
	if(IsEmpty()) {
		std::runtime_error("Attempt to Dequeue an empty RandomizedQueue");
	}
	auto indexOfValToRemove = GetRandomInt(0, MaxIndex());
	std::swap((*m_queue)[indexOfValToRemove], (*m_queue)[MaxIndex()]);
	auto valToRemove = (*m_queue)[MaxIndex()];
	m_queue->PopBack();
	return valToRemove;
}

template<typename T>
T RandomizedQueue<T>::Sample() {
	if(IsEmpty()) {
		std::runtime_error("Attempt to Sample an empty RandomizedQueue");
	}
	auto indexOfValToSample = GetRandomInt(0, MaxIndex());
	return (*m_queue)[indexOfValToSample];
}

template<typename T>
RandomizedQueueNext<T> RandomizedQueue<T>::CreateNext() const {
	return RandomizedQueueNext(m_queue);
}

