#pragma once
#include "Stack.h"
#include <assert.h>


template<typename T>
class StackArray : public Stack<T> {
public:
	StackArray(int maxSize = 100);
	StackArray(const StackArray& rhs);
	StackArray& operator=(const StackArray& rhs);
	StackArray(StackArray&& rhs) noexcept;
	StackArray& operator=(StackArray&& rhs) noexcept;

	virtual void Reinitialize() override;
	virtual bool IsEmpty() const override;
	virtual bool IsFull() const override;
	virtual void Pop() override;
	virtual void Push(const T&) override;
	virtual T Top() const override;

	virtual ~StackArray();
private:
	void CopyMembers(const StackArray& rhs);

	int m_capacity{100};
	int m_top1Base{0};
	T * m_list = nullptr;
};

template <typename T>	
void StackArray<T>::CopyMembers(const StackArray& rhs) {
	m_capacity = rhs.m_capacity;
	m_list = new T [m_capacity]();
	m_top1Base = 0;
	while(m_top1Base < rhs.m_top1Base) {
		m_list[m_top1Base] = rhs.m_list[m_top1Base];
		++m_top1Base;
	}	
}

template <typename T>
StackArray<T>::StackArray(int maxSize) : m_capacity(maxSize), m_list(new T [m_capacity]()) {}

template <typename T>
StackArray<T>::StackArray(const StackArray& rhs) {CopyMembers(rhs);}

template <typename T>
StackArray<T>::StackArray(StackArray && rhs) noexcept
    : m_capacity(rhs.m_capacity), m_top1Base(rhs.m_top1Base), m_list(rhs.m_list) {
    rhs.m_list = nullptr;
} 


template <typename T> StackArray<T>::~StackArray() {
	delete[] m_list;
}

template <typename T> StackArray<T>& StackArray<T>::operator=(const StackArray& rhs) {
	if(this != &rhs) {
		delete[] m_list;
		CopyMembers(rhs);
	}
	return *this;
}


template <typename T> StackArray<T>& StackArray<T>::operator=(StackArray&& rhs) noexcept {
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
bool StackArray<T>::IsEmpty() const {
	return m_top1Base == 0; 
}

template <typename T> 
bool StackArray<T>::IsFull() const {
	return m_top1Base == m_capacity;
}

template <typename T>
void StackArray<T>::Pop() {
	assert(!IsEmpty());
	--m_top1Base;
}

template <typename T>
void StackArray<T>::Push(const T& t) {
	assert(!IsFull());
	m_list[m_top1Base] = t;
	++m_top1Base;
}

template <typename T>
T StackArray<T>::Top() const {
	assert(!IsEmpty());
	return m_list[m_top1Base - 1];
}

template <typename T>
void StackArray<T>::Reinitialize() {
	m_top1Base = 0;
}