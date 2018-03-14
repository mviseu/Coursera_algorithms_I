#pragma once
#include "Stack.h"
#include <assert.h>
#include <cmath>


template<typename T>
class Vector {
public:
	Vector();
	Vector(const Vector& rhs);
	Vector& operator=(const Vector& rhs);
	Vector(Vector&& rhs) noexcept;
	Vector& operator=(Vector&& rhs) noexcept;

	void Reinitialize();
	int Size() const;
	bool IsEmpty() const;
	bool IsFull() const;
	void PopBack();
	void PushBack(const T&);
	T Back() const;
	const T& operator[](int i) const;
	T& operator[](int i);

	~Vector();
private:
	T& DoSubscript(int i) const;
	void CopyMembers(const Vector& rhs);
	bool IsQuarterFull() const;

	int m_capacity{0};
	int m_size{0};
	T * m_resizableArray = nullptr;
};

template <typename T>	
void Vector<T>::CopyMembers(const Vector& rhs) {
	m_capacity = rhs.m_capacity;
	m_resizableArray = new T [m_capacity]();
	m_size = 0;
	while(m_size < rhs.m_size) {
		m_resizableArray[m_size] = rhs.m_resizableArray[m_size];
		++m_size;
	}	
}

namespace {

template <typename T>
T* ResizeArray(int capacity, int size, T* resizableArray) {
	auto newResizableArray = new T[capacity]();
	for(auto j = 0; j < size; ++j) {
		newResizableArray[j] = resizableArray[j];
	}
	delete [] resizableArray;
	resizableArray = newResizableArray;
	newResizableArray = nullptr;
	return resizableArray;
}

} // namespace

template <typename T>
Vector<T>::Vector() {}

template <typename T>
Vector<T>::Vector(const Vector& rhs) {CopyMembers(rhs);}

template <typename T>
Vector<T>::Vector(Vector && rhs) noexcept
    : m_capacity(rhs.m_capacity), m_size(rhs.m_size), m_resizableArray(rhs.m_resizableArray) {
    rhs.m_resizableArray = nullptr;
} 


template <typename T> Vector<T>::~Vector() {
	delete[] m_resizableArray;
}

template <typename T> Vector<T>& Vector<T>::operator=(const Vector& rhs) {
	if(this != &rhs) {
		delete[] m_resizableArray;
		CopyMembers(rhs);
	}
	return *this;
}


template <typename T> Vector<T>& Vector<T>::operator=(Vector&& rhs) noexcept {
	if(this != &rhs) {
		delete[] m_resizableArray;
		m_capacity = rhs.m_capacity;
		m_size = rhs.m_size;
		m_resizableArray = rhs.m_resizableArray;
		rhs.m_resizableArray = nullptr;
	}
	return *this;
}


template <typename T> 
int Vector<T>::Size() const {
	return m_size; 
}

template <typename T> 
bool Vector<T>::IsEmpty() const {
	return m_size == 0; 
}

template <typename T> 
bool Vector<T>::IsFull() const {
	return m_size == m_capacity;
}

template <typename T> 
bool Vector<T>::IsQuarterFull() const {
	return m_size == 0.25 * m_capacity;	
}

template <typename T>
void Vector<T>::PopBack() {
	assert(!IsEmpty());
	if(IsQuarterFull()) {
		m_capacity = m_capacity / 2;
		m_resizableArray = ResizeArray(m_capacity, m_size, m_resizableArray);
	}
	--m_size;
}

template <typename T>
void Vector<T>::PushBack(const T& t) {
	if(IsFull()) {
		if(m_capacity) {
			m_capacity = 2 * m_capacity;
		} else {
			m_capacity = 1;
		}
		m_resizableArray = ResizeArray(m_capacity, m_size, m_resizableArray);
	}
	m_resizableArray[m_size] = t;
	++m_size;
}



template <typename T>
T Vector<T>::Back() const {
	assert(!IsEmpty());
	return m_resizableArray[m_size - 1];
}


template <typename T>
void Vector<T>::Reinitialize() {
	delete [] m_resizableArray;
	m_size = 0;
	m_capacity = 0;
}

template <typename T>
T& Vector<T>::DoSubscript(int i) const {
	assert(i < m_size);
	return const_cast<T&>(m_resizableArray[i]);
}

template <typename T>
const T& Vector<T>::operator[](int i) const {
	return DoSubscript(i);
}

template <typename T>
T& Vector<T>::operator[](int i) {
	return DoSubscript(i);
}