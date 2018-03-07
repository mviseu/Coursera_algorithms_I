#pragma once
#include "Queue.h"
#include <iostream>
#include <assert.h>


template <typename T> 
class QueueLinkedList : public Queue<T> {
public:
	QueueLinkedList() = default;
	
	QueueLinkedList(const QueueLinkedList&);
	QueueLinkedList(QueueLinkedList&&) noexcept;

	
	QueueLinkedList& operator=(const QueueLinkedList&);
	QueueLinkedList& operator=(QueueLinkedList&&) noexcept;
	
	void Enqueue(const T&) override;
	void Dequeue() override;
	bool IsEmpty() const override;
	bool IsFull() const override;
	
	
	T First() const override;
	T Last() const override;
	void Reinitialize() override;
	~QueueLinkedList() noexcept;

private:
	void Copy(const QueueLinkedList& rhs);

	struct Node {
		T elem = T();
		Node* next = nullptr;
	};

	Node* m_first = nullptr;
	Node* m_last = nullptr;
};

template<typename T>
void QueueLinkedList<T>::Copy(const QueueLinkedList& rhs) {
	if(!rhs.IsEmpty()) {
		auto ptrToRhs = rhs.m_first;
		Node* newNode = new Node {ptrToRhs->elem, nullptr};
		m_first = newNode;
		while((ptrToRhs = ptrToRhs->next)) {
			newNode->next = new Node {ptrToRhs->elem, nullptr};
			newNode = newNode->next;
		}
		m_last = newNode;
	}
}

template<typename T>
QueueLinkedList<T>::QueueLinkedList(const QueueLinkedList& rhs) {
	Copy(rhs);
}

template<typename T>
QueueLinkedList<T>::QueueLinkedList(QueueLinkedList&& rhs) noexcept
: m_first(rhs.m_first), m_last(rhs.m_last) 
{
	rhs.m_first = rhs.m_last = nullptr;
}

template<typename T>
QueueLinkedList<T>& QueueLinkedList<T>::operator=(const QueueLinkedList& rhs) {
	if(this != &rhs) {
		Reinitialize();
		Copy(rhs);
	}
	return *this;
}

template<typename T>
QueueLinkedList<T>& QueueLinkedList<T>::operator=(QueueLinkedList&& rhs) noexcept {
	if(this != &rhs) {
		m_first = rhs.m_first;
		m_last = rhs.m_last;
		rhs.m_first = rhs.m_last = nullptr;
	}
	return *this;
}

template<typename T>
QueueLinkedList<T>::~QueueLinkedList() noexcept {
	Reinitialize();
}


template<typename T>
bool QueueLinkedList<T>::IsEmpty() const {
	return !m_first;
}

template<typename T>
bool QueueLinkedList<T>::IsFull() const {
	return false;
}

template<typename T>
T QueueLinkedList<T>::First() const {
	assert(!IsEmpty());
	return m_first->elem;
}

template<typename T>
T QueueLinkedList<T>::Last() const {
	assert(!IsEmpty());
	return m_last->elem;
}

template<typename T>
void QueueLinkedList<T>::Reinitialize() {
	while(!IsEmpty()) {
		Dequeue();
	}
}

template<typename T>
void QueueLinkedList<T>::Enqueue(const T& item) {
	Node* newNode = new Node {item, nullptr};
	if(!IsEmpty()) {
		m_last->next = newNode;
	} else {
		m_first = newNode;
	}
	m_last = newNode;
	newNode = nullptr;
}


template<typename T>
void QueueLinkedList<T>::Dequeue() {
	assert(!IsEmpty());
	auto oldFirst = m_first;
	m_first = oldFirst->next;
	if(IsEmpty()) {
		m_first = m_last = nullptr;
	}
	delete oldFirst;
	oldFirst = nullptr;
}
