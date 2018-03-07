#pragma once
#include "Queue.h"
#include <iostream>
#include <assert.h>


template <typename T> 
class QueueResizeArray : public Queue<T> {
public:
	QueueResizeArray() = default;
	QueueResizeArray(const QueueResizeArray&);
	
	QueueResizeArray(QueueResizeArray&&) noexcept;
	QueueResizeArray& operator=(const QueueResizeArray&);
	QueueResizeArray& operator=(QueueResizeArray&&) noexcept;

	void Enqueue(const T&) override;
	void Dequeue() override;
	bool IsEmpty() const override;
	bool IsFull() const override;
	bool IsLastEnd() const;
	
	T First() const override;
	T Last() const override;
	
	void Reinitialize() override;
	~QueueResizeArray() noexcept;

private:
	bool IsQuarterFull() const;
	void CopyMembers(const QueueResizeArray& rhs);
	void HalveCapacityAndShift();
	void DoubleCapacity();

	int m_capacity{0};
	int m_first{0}; //1 based
	int m_last{0}; // 1 based
	T * m_arr = nullptr;
};


template<typename T> 
void QueueResizeArray<T>::CopyMembers(const QueueResizeArray& rhs) {
	m_capacity = rhs.m_capacity;
	m_first = rhs.m_first;
	m_last = rhs.m_last;
	m_arr = new T[m_capacity]();
	for(auto i = m_first; i < m_first + m_last - m_first; ++i) {
		m_arr[i - 1] = rhs.m_arr[i - 1];
	}
}

template<typename T> 
QueueResizeArray<T>::QueueResizeArray(const QueueResizeArray& rhs) {
	CopyMembers(rhs);
}

template<typename T> 
QueueResizeArray<T>::QueueResizeArray(QueueResizeArray&& rhs) noexcept 
: m_capacity(rhs.m_capacity), m_first(rhs.m_first), m_last(rhs.m_last), m_arr(rhs.m_arr) {
	rhs.m_arr = nullptr;
}

template<typename T> 
QueueResizeArray<T>::~QueueResizeArray() noexcept {
	delete [] m_arr;
}

template<typename T> 
QueueResizeArray<T>& QueueResizeArray<T>::operator=(const QueueResizeArray& rhs) {
	if(this != &rhs) {
		delete [] m_arr;
		CopyMembers(rhs);		
	}
	return *this;
}

template<typename T> 
QueueResizeArray<T>& QueueResizeArray<T>::operator=(QueueResizeArray&& rhs) noexcept {
	if(this != &rhs) {
		delete [] m_arr;
		m_capacity = rhs.m_capacity;
		m_first = rhs.m_first;
		m_last = rhs.m_last;
		m_arr = rhs.m_arr;
		rhs.m_arr = nullptr;		
	}
	return *this;
}

template<typename T>
void QueueResizeArray<T>::Reinitialize() {
	delete [] m_arr;
	m_arr = nullptr;
	m_capacity = m_first = m_last = 0;
}


template <typename T>
bool QueueResizeArray<T>::IsEmpty() const {
	return m_first == m_last;
}

template <typename T>
bool QueueResizeArray<T>::IsFull() const {
	return m_last - m_first == m_capacity;
}

template <typename T>
bool QueueResizeArray<T>::IsLastEnd() const {
	return m_last == m_capacity + 1;
}


template <typename T>
bool QueueResizeArray<T>::IsQuarterFull() const {
	return m_last - m_first == 0.25 * m_capacity;
}

template <typename T>
T QueueResizeArray<T>::First() const {
	assert(!IsEmpty());
	return m_arr[m_first - 1];
}

template <typename T>
T QueueResizeArray<T>::Last() const {
	assert(!IsEmpty());
	return m_arr[m_last - 2];	
}

template <typename T>
void QueueResizeArray<T>::HalveCapacityAndShift() {
	m_capacity = m_capacity / 2;
	auto new_arr = new T[m_capacity]();
	for(auto i = 1; i < m_last - m_first; ++i) {
		new_arr[i - 1] = m_arr[i + m_first - 1];
	}
	delete [] m_arr;
	m_arr = new_arr;
	new_arr = nullptr;
	m_last = m_last - m_first;
	m_first = 1;
}

template <typename T>
void QueueResizeArray<T>::Dequeue() {
	assert(!IsEmpty());
	if(IsQuarterFull()) {
		HalveCapacityAndShift();
	} else {
		++m_first;
	}
	if(IsEmpty()) {
		delete [] m_arr;
		m_arr = nullptr;
		m_capacity = m_first = m_last = 0;
	}
}

template <typename T>
void QueueResizeArray<T>::DoubleCapacity() {
	if(m_capacity) {
		m_capacity = 2 * m_capacity;
	} else {
		m_capacity = 1;
	}
	auto new_arr = new T[m_capacity]();
	for(auto i = 0; i < m_last - m_first; ++i) {
		new_arr[i] = m_arr[i + m_first - 1];
	}
	delete [] m_arr;
	m_arr = new_arr;
	new_arr = nullptr;
}

template <typename T>
void QueueResizeArray<T>::Enqueue(const T& elem) {
	auto new_first{1};
	if(IsFull()) {
		DoubleCapacity();
	} else {
		if(IsLastEnd()) {
			for(auto i = 0; i < m_last - m_first; ++i) {
				m_arr[i] = m_arr[i + m_first - 1];
			}
		} else {
			new_first = m_first;
		}
	}
	m_arr[m_last - m_first + new_first - 1] = elem;
	m_last = m_last - m_first + 1 + new_first;
	m_first = new_first;
}