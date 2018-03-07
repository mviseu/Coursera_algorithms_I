#pragma once
#include "Queue.h"
#include <iostream>
#include <assert.h>


template <typename T> 
class QueueLinkedList : public Queue<T> {
public:
	QueueLinkedList() = default;
	/*
	QueueLinkedList(const QueueLinkedList&);
	
	QueueLinkedList(QueueLinkedList&&) noexcept;
	QueueLinkedList& operator=(const QueueLinkedList&);
	QueueLinkedList& operator=(QueueLinkedList&&) noexcept;
	*/
	void Enqueue(const T&) override;
	void Dequeue() override;
	bool IsEmpty() const override;
	bool IsFull() const override;
	
	/*
	T First() const override;
	T Last() const override;
	
	void Reinitialize() override;
	*/
	~QueueLinkedList() noexcept;

private:
	struct Node {
		T elem = T();
		Node* next = nullptr;
	};

	Node* m_first = nullptr;
	Node* m_last = nullptr;
};

template<typename T>
QueueLinkedList<T>::~QueueLinkedList() noexcept {
	while(!IsEmpty()) {
		Dequeue();
	}
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
