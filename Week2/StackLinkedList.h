#pragma once
#include "Stack.h"
#include <assert.h>

template<typename T>
class StackLinkedList : public Stack<T> {
public:
	StackLinkedList(int size = 100);
	StackLinkedList(const StackLinkedList& rhs);
	StackLinkedList& operator=(const StackLinkedList& rhs);
	StackLinkedList(StackLinkedList&& rhs) noexcept;
	StackLinkedList& operator=(StackLinkedList&& rhs) noexcept;

	virtual void Reinitialize() override;
	virtual bool IsEmpty() const override;
	virtual bool IsFull() const override;
	virtual void Pop() override;
	virtual void Push(const T&) override;
	virtual T Top() const override;

	virtual ~StackLinkedList();
private:
	struct Node {
		T item = T();
		Node* next = nullptr;
	};
	Node* top = nullptr;
};

template <typename T>
StackLinkedList<T>::StackLinkedList(int size) {
	top = new Node();
	for(int j = 0; j < size - 1; ++j) {
		auto after = top;
		top = new Node();
		top->next = after;
	}
}

/*
template <typename T>
StackLinkedList<T>::StackLinkedList(const StackLinkedList& rhs) {
	auto j = rhs.top;
	while(j->next) {j = j->next;}
	while(j != rhs.top) {Push(j->item);}
}
*/

template <typename T>
StackLinkedList<T>::~StackLinkedList() {
	while(!IsEmpty()) {
		Pop();
	}
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
	top = new Node{elem, oldTop};
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