#pragma once
#include "RandomIntGenerator.h"
#include "Vector.h"
#include <functional>
#include <memory>
#include <stdexcept>
#include <utility>

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

std::shared_ptr<Vector<T>> m_queue; // assignment assumes queue is not changed whilst using Next()
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
	return (*m_queue)[m_randomIndexes[old_count]];
}

template<typename T>
bool RandomizedQueueNext<T>::HasNext() const {
	CheckForQueueChange();
	return m_count < m_randomIndexes.Size();
}

template<typename T>
void RandomizedQueueNext<T>::CheckForQueueChange() const {
	if(m_hashNr != std::hash<Vector<T>>()(*m_queue)) {
		throw std::runtime_error("Change queue detected. Cannot use RandomizedQueueNextNext");
	}
}

template<typename T>
void RandomizedQueueNext<T>::CheckIfNotHasNext() const {
	if(!HasNext()) {
		throw std::runtime_error("RandomizedQueueNext does not have the next random item!");
	}
}