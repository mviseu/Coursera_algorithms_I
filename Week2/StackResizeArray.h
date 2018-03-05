#pragma once
#include "Stack.h"
#include <assert.h>
#include <cmath>


template<typename T>
class StackResizeArray : public Stack<T> {
public:
	StackResizeArray();
	StackResizeArray(const StackResizeArray& rhs);
	StackResizeArray& operator=(const StackResizeArray& rhs);
	StackResizeArray(StackResizeArray&& rhs) noexcept;
	StackResizeArray& operator=(StackResizeArray&& rhs) noexcept;

	virtual void Reinitialize() override;
	virtual bool IsEmpty() const override;
	virtual bool IsFull() const override;
	virtual void Pop() override;
	virtual void Push(const T&) override;
	virtual T Top() const override;

	virtual ~StackResizeArray();
private:
	void CopyMembers(const StackResizeArray& rhs);
	bool IsQuarterFull() const;

	int m_capacity{0};
	int m_top1Base{0};
	T * m_list = nullptr;
};

template <typename T>	
void StackResizeArray<T>::CopyMembers(const StackResizeArray& rhs) {
	m_capacity = rhs.m_capacity;
	m_list = new T [m_capacity]();
	m_top1Base = 0;
	while(m_top1Base < rhs.m_top1Base) {
		m_list[m_top1Base] = rhs.m_list[m_top1Base];
		++m_top1Base;
	}	
}

namespace {

template <typename T>
T* ResizeList(int capacity, int top1Base, T* list) {
	auto new_list = new T[capacity]();
	for(auto j = 0; j < top1Base; ++j) {
		new_list[j] = list[j];
	}
	delete [] list;
	list = new_list;
	new_list = nullptr;
	return list;
}

} // namespace

template <typename T>
StackResizeArray<T>::StackResizeArray() {}

template <typename T>
StackResizeArray<T>::StackResizeArray(const StackResizeArray& rhs) {CopyMembers(rhs);}

template <typename T>
StackResizeArray<T>::StackResizeArray(StackResizeArray && rhs) noexcept
    : m_capacity(rhs.m_capacity), m_top1Base(rhs.m_top1Base), m_list(rhs.m_list) {
    rhs.m_list = nullptr;
} 


template <typename T> StackResizeArray<T>::~StackResizeArray() {
	delete[] m_list;
}

template <typename T> StackResizeArray<T>& StackResizeArray<T>::operator=(const StackResizeArray& rhs) {
	if(this != &rhs) {
		delete[] m_list;
		CopyMembers(rhs);
	}
	return *this;
}


template <typename T> StackResizeArray<T>& StackResizeArray<T>::operator=(StackResizeArray&& rhs) noexcept {
	if(this != &rhs) {
		delete[] m_list;
		m_capacity = rhs.m_capacity;
		m_top1Base = rhs.m_top1Base;
		m_list = rhs.m_list;
		rhs.m_list = nullptr;
	}
	return *this;
}

template <typename T> 
bool StackResizeArray<T>::IsEmpty() const {
	return m_top1Base == 0; 
}

template <typename T> 
bool StackResizeArray<T>::IsFull() const {
	return m_top1Base == m_capacity;
}

template <typename T> 
bool StackResizeArray<T>::IsQuarterFull() const {
	return m_top1Base == 0.25 * m_capacity;	
}

template <typename T>
void StackResizeArray<T>::Pop() {
	assert(!IsEmpty());
	if(IsQuarterFull()) {
		m_capacity = m_capacity / 2;
		m_list = ResizeList(m_capacity, m_top1Base, m_list);
	}
	--m_top1Base;
}

template <typename T>
void StackResizeArray<T>::Push(const T& t) {
	if(IsFull()) {
		if(m_capacity) {
			m_capacity = 2 * m_capacity;
		} else {
			m_capacity = 1;
		}
		m_list = ResizeList(m_capacity, m_top1Base, m_list);
	}
	m_list[m_top1Base] = t;
	++m_top1Base;
}



template <typename T>
T StackResizeArray<T>::Top() const {
	assert(!IsEmpty());
	return m_list[m_top1Base - 1];
}


template <typename T>
void StackResizeArray<T>::Reinitialize() {
	delete [] m_list;
	m_top1Base = 0;
	m_capacity = 0;
}
