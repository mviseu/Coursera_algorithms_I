#pragma once
#include "Stack.h"
#include "StackLinkedListIt.h"
#include <assert.h>
#include <iostream>
#include <type_traits>

template<typename T>
struct Node {
	T item = T();
	Node* next = nullptr;
};

template<typename T, typename UnqualifiedT = std::remove_cv_t<T>>
class StackLinkedList : public Stack<T> {

public:
	using iterator = StackLinkedListIt<T>;
	using const_iterator = StackLinkedListIt<const T>;

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

	iterator begin() const;
	const_iterator cbegin() const;
	iterator end() const;
	const_iterator cend() const;

private:
	void CopyStack(const StackLinkedList& rhs);
	Node<UnqualifiedT>* top = nullptr;
};

template <typename T, typename UnqualifiedT>
StackLinkedList<T, UnqualifiedT>::StackLinkedList(int size) {
	for(int j = 0; j < size; ++j) {
		auto old_top = top;
		top = new Node<T>();
		top->next = old_top;
	}
}


template<typename T, typename UnqualifiedT>
void StackLinkedList<T, UnqualifiedT>::CopyStack(const StackLinkedList& rhs) {
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

template <typename T, typename UnqualifiedT>
StackLinkedList<T, UnqualifiedT>::StackLinkedList(const StackLinkedList& rhs) {
	#ifdef DEBUG
		std::cout << "Copy constructor" << std::endl;
	#endif
	CopyStack(rhs);
}

template <typename T, typename UnqualifiedT>
StackLinkedList<T, UnqualifiedT>::StackLinkedList(StackLinkedList&& rhs) noexcept {
	#ifdef DEBUG
		std::cout << "Move constructor" << std::endl;
	#endif
	top = rhs.top;
	rhs.top = nullptr;
}

template <typename T, typename UnqualifiedT>
StackLinkedList<T, UnqualifiedT>& StackLinkedList<T, UnqualifiedT>::operator=(const StackLinkedList& rhs) {
	if(this != &rhs) {
		Reinitialize();
		CopyStack(rhs);
	}
	return *this;
}

template <typename T, typename UnqualifiedT>
StackLinkedList<T, UnqualifiedT>& StackLinkedList<T, UnqualifiedT>::operator=(StackLinkedList&& rhs) noexcept {
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

template <typename T, typename UnqualifiedT>
void StackLinkedList<T, UnqualifiedT>::Reinitialize() {
	while(!IsEmpty()) {
		Pop();
	}
}

template <typename T, typename UnqualifiedT>
StackLinkedList<T, UnqualifiedT>::~StackLinkedList() {
	Reinitialize();
}

template <typename T, typename UnqualifiedT>
bool StackLinkedList<T, UnqualifiedT>::IsEmpty() const {
	return !top;
}

template <typename T, typename UnqualifiedT>
bool StackLinkedList<T, UnqualifiedT>::IsFull() const {
	return false;
}

template <typename T, typename UnqualifiedT>
void StackLinkedList<T, UnqualifiedT>::Push(const T& elem) {
	auto oldTop = top;
	top = new Node<T>{elem, oldTop};
}

template <typename T, typename UnqualifiedT>
void StackLinkedList<T, UnqualifiedT>::Pop() {
	assert(!IsEmpty());
	auto newTop = top->next;
	delete top;
	top = newTop;
}

template <typename T, typename UnqualifiedT>
T StackLinkedList<T, UnqualifiedT>::Top() const {
	assert(!IsEmpty());
	return top->item;
}

template <typename T, typename UnqualifiedT>
typename StackLinkedList<T, UnqualifiedT>::iterator StackLinkedList<T, UnqualifiedT>::begin() const {
	return StackLinkedListIt<T>(top);
}

template <typename T, typename UnqualifiedT>
typename StackLinkedList<T, UnqualifiedT>::const_iterator StackLinkedList<T, UnqualifiedT>::cbegin() const {
	return begin();
}

template <typename T, typename UnqualifiedT>
typename StackLinkedList<T, UnqualifiedT>::iterator StackLinkedList<T, UnqualifiedT>::end() const {
	return iterator();
}

template <typename T, typename UnqualifiedT>
typename StackLinkedList<T, UnqualifiedT>::const_iterator StackLinkedList<T, UnqualifiedT>::cend() const {
	return end();
}