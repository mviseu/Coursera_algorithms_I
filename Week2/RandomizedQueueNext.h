#pragma once
#include "RandomIntGenerator.h"
#include "Vector.h"
#include <memory>
#include <stdexcept>
#include <utility>


template <typename T> class RandomizedQueue;

template <typename T>
class RandomizedQueueNext {
public:
RandomizedQueueNext(const Vector<T>& vec);
RandomizedQueueNext(const RandomizedQueueNext&) = delete;
RandomizedQueueNext& operator=(const RandomizedQueueNext&) =  delete;
T Next();
bool HasNext() const;

private:
std::unique_ptr<Vector<T>> m_vec;
int m_count{0};
};


template<typename T> 
RandomizedQueueNext<T>::RandomizedQueueNext(const Vector<T>& vec) 
: m_vec(std::make_unique<Vector<T>>(vec)) {}


template<typename T>
T RandomizedQueueNext<T>::Next() {
	if(!HasNext()) {
		throw std::runtime_error("RandomizedQueueNext does not have the next random item!");
	}
	auto old_count = m_count;
	auto randomIndex = GetRandomInt(old_count, m_vec->Size() - 1);
	std::swap((*m_vec)[old_count], (*m_vec)[randomIndex]);
	++m_count;
	return (*m_vec)[old_count];
}

template<typename T>
bool RandomizedQueueNext<T>::HasNext() const{
	return m_count < m_vec->Size();
}
