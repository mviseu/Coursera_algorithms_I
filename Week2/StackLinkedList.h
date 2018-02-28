#pragma once
#include "Stack.h"
#include <assert.h>

template<typename T>
class StackLinkedList : public Stack<T> {
public:
	StackLinkedList(int size = 0);
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
	void CopyStack(const StackLinkedList& rhs);
	struct Node {
		T item = T();
		Node* next = nullptr;
	};
	Node* top = nullptr;
};

template <typename T>
StackLinkedList<T>::StackLinkedList(int size) {
	for(int j = 0; j < size; ++j) {
		auto old_top = top;
		top = new Node();
		top->next = old_top;
	}
}


template<typename T>
void StackLinkedList<T>::CopyStack(const StackLinkedList& rhs) {
	if(!rhs.IsEmpty()) {
		auto curr = rhs.top;
		top = new Node{curr->item, nullptr};
		auto before = top;
		while((curr = curr->next)) {
			auto after = new Node{curr->item, nullptr};
			before->next = after;
			before = after;
		}
	}
}

template <typename T>
StackLinkedList<T>::StackLinkedList(const StackLinkedList& rhs) {
	CopyStack(rhs);
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