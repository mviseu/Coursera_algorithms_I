#pragma once
#include "RandomIntGenerator.h"
#include "Vector.h"
#include <functional>
#include <memory>
#include <stdexcept>
#include <utility>
#include <iostream>

namespace {
template <typename T>
void ShuffleIndexes(Vector<T>& vec) {
	for(auto i = 0; i < vec.Size(); ++i) {
		auto randomIndex = GetRandomInt(0, vec.Size() - 1);
		std::swap(vec[i], vec[randomIndex]);
	}
}
} // namespace

template <typename T> class RandomizedQueue;

template <typename T>
class RandomizedQueueNext {
public:
RandomizedQueueNext(std::shared_ptr<Vector<T>> queue);
RandomizedQueueNext(const RandomizedQueueNext&) = delete;
RandomizedQueueNext& operator=(const RandomizedQueueNext&) =  delete;
T Next();
bool HasNext() const;

private:
void CheckForQueueChange() const;
void CheckIfNotHasNext() const;
std::shared_ptr<Vector<T>> GetQueue() const;

std::weak_ptr<Vector<T>> m_queue; // does not control queue lifetime
Vector<int> m_randomIndexes;
int m_count{0}; // due to requirement on constant worst-case (not amortized)
std::size_t m_hashNr; // to detect when queue changes so Next, HasNext can fail

};


template<typename T> 
RandomizedQueueNext<T>::RandomizedQueueNext(std::shared_ptr<Vector<T>> queue) 
: m_queue(queue), m_hashNr(std::hash<Vector<T>>()(*queue)) {
	// create a shuffled Vector of indexes
	for(auto i = 0; i < queue->Size(); ++i) {
		m_randomIndexes.PushBack(i);
	}
	ShuffleIndexes(m_randomIndexes);
}


template<typename T>
T RandomizedQueueNext<T>::Next() {
	CheckForQueueChange();
	CheckIfNotHasNext();
	auto old_count = m_count;
	++m_count;
	auto queue = GetQueue();
	return (*queue)[m_randomIndexes[old_count]];
}

template<typename T>
bool RandomizedQueueNext<T>::HasNext() const {
	CheckForQueueChange();
	auto queue = GetQueue();
	return m_count < queue->Size();
}

template<typename T>
void RandomizedQueueNext<T>::CheckForQueueChange() const {
	auto queue = GetQueue();
	if(m_hashNr != std::hash<Vector<T>>()(*queue)) {
		throw std::runtime_error("Change queue detected. Cannot use RandomizedQueueNext");
	}
}

template<typename T>
void RandomizedQueueNext<T>::CheckIfNotHasNext() const {
	if(!HasNext()) {
		throw std::runtime_error("RandomizedQueueNext does not have the next random item!");
	}
}

template<typename T>
std::shared_ptr<Vector<T>> RandomizedQueueNext<T>::GetQueue() const {
	auto sptr = m_queue.lock();
	if(sptr) {
		std::cout << sptr.use_count() << std::endl;
		return sptr;
	} else {
		throw std::runtime_error("Attempt to access a RandomizedQueue that no longer exists");
	}
}