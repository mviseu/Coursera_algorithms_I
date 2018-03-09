#pragma once
#include "Stack.h"
#include "StackLinkedListIt.h"
#include <assert.h>
#include <iostream>

template<typename T>
struct Node {
	T item = T();
	Node* next = nullptr;
};

template<typename T>
class StackLinkedList : public Stack<T> {

using iterator = StackLinkedListIt<T>;
using const_iterator = StackLinkedListIt<const T>;

public:
	StackLinkedList(int size = 0);
	StackLinkedList(const StackLinkedList& rhs);
	StackLinkedList& operator=(const StackLinkedList& rhs);
	StackLinkedList(StackLinkedList&& rhs) noexcept;
	StackLinkedList& operator=(StackLinkedList&& rhs) noexcept;
	virtual ~StackLinkedList();

	virtual void Reinitialize() override;
	virtual bool IsEmpty() const override;
	virtual bool IsFull() const override;
	virtual void Pop() override;
	virtual void Push(const T&) override;
	virtual T Top() const override;

	//iterator begin() const;
	//const_iterator cbegin() const;

private:
	void CopyStack(const StackLinkedList& rhs);
	Node<T>* top = nullptr;
};

template <typename T>
StackLinkedList<T>::StackLinkedList(int size) {
	for(int j = 0; j < size; ++j) {
		auto old_top = top;
		top = new Node<T>();
		top->next = old_top;
	}
}


template<typename T>
void StackLinkedList<T>::CopyStack(const StackLinkedList& rhs) {
	if(!rhs.IsEmpty()) {
		auto curr = rhs.top;
		top = new Node<T>{curr->item, nullptr};
		auto before = top;
		while((curr = curr->next)) {
			auto after = new Node<T>{curr->item, nullptr};
			before->next = after;
			before = after;
		}
	}
}

template <typename T>
StackLinkedList<T>::StackLinkedList(const StackLinkedList& rhs) {
	#ifdef DEBUG
		std::cout << "Copy constructor" << std::endl;
	#endif
	CopyStack(rhs);
}

template <typename T>
StackLinkedList<T>::StackLinkedList(StackLinkedList&& rhs) noexcept {
	#ifdef DEBUG
		std::cout << "Move constructor" << std::endl;
	#endif
	top = rhs.top;
	rhs.top = nullptr;
}

template <typename T>
StackLinkedList<T>& StackLinkedList<T>::operator=(const StackLinkedList& rhs) {
	if(this != &rhs) {
		Reinitialize();
		CopyStack(rhs);
	}
	return *this;
}

template <typename T>
StackLinkedList<T>& StackLinkedList<T>::operator=(StackLinkedList&& rhs) noexcept {
	#ifdef DEBUG
		std::cout << "Move assignment" << std::endl;
	#endif
	if(this != &rhs) {
		Reinitialize();
		top = rhs.top;
		rhs.top = nullptr;
	}
	return *this;
}

template <typename T>
void StackLinkedList<T>::Reinitialize() {
	while(!IsEmpty()) {
		Pop();
	}
}

template <typename T>
StackLinkedList<T>::~StackLinkedList() {
	Reinitialize();
}

template <typename T>
bool StackLinkedList<T>::IsEmpty() const {
	return !top;
}

template <typename T>
bool StackLinkedList<T>::IsFull() const {
	return false;
}

template <typename T>
void StackLinkedList<T>::Push(const T& elem) {
	auto oldTop = top;
	top = new Node<T>{elem, oldTop};
}

template <typename T>
void StackLinkedList<T>::Pop() {
	assert(!IsEmpty());
	auto newTop = top->next;
	delete top;
	top = newTop;
}

template <typename T>
T StackLinkedList<T>::Top() const {
	assert(!IsEmpty());
	return top->item;
}

/*
See how to construct

template <typename T>
typename StackLinkedList<T>::iterator StackLinkedList<T>::begin() const {
	return iterator(top);
}


template <typename T>
typename StackLinkedList<T>::const_iterator StackLinkedList<T>::cbegin() const {
	return begin();
}
*/