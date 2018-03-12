#pragma once
#include "BidirectionalLinkedListIt.h"
#include <memory>
#include <type_traits>

template <typename T>
struct Node {
Node(const T& itm, std::shared_ptr<Node> pr, std::shared_ptr<Node> nt) : item(itm), prev(pr), next(nt) {}

T item = T();
std::shared_ptr<Node> prev;
std::shared_ptr<Node> next;
};

template <typename T, typename UnqualifiedT = typename std::remove_cv<T>::type>
class BidirectionalLinkedList {
public:
using iterator = BidirectionalLinkedListIt<T>;
using const_iterator = BidirectionalLinkedListIt<const T>;
using reverse_iterator = std::reverse_iterator<iterator>;
using const_reverse_iterator = std::reverse_iterator<const_iterator>;


BidirectionalLinkedList();
bool IsEmpty() const;
int Size() const;
void PushFront(const T& itm);
void PushBack(const T& itm);
void PopFront();
void PopBack();

iterator begin() const;
iterator end() const;
const_iterator cbegin() const;
const_iterator cend() const;
reverse_iterator rbegin() const;
reverse_iterator rend() const;
const_reverse_iterator crbegin() const;
const_reverse_iterator crend() const;

private:
void PopWhenEmpty();

int m_size{0};
std::shared_ptr<Node<UnqualifiedT>> m_beforeFront = nullptr;
std::shared_ptr<Node<UnqualifiedT>> m_afterBack = nullptr;
};


template <typename T, typename UnqualifiedT>
BidirectionalLinkedList<T, UnqualifiedT>::BidirectionalLinkedList() 
{
	m_size = 0;
	m_beforeFront = std::make_shared<Node<T>>(T(), nullptr, nullptr);
	m_afterBack = std::make_shared<Node<T>>(T(), m_beforeFront, nullptr);
	m_beforeFront->next = m_afterBack;
}

template <typename T, typename UnqualifiedT>
bool BidirectionalLinkedList<T, UnqualifiedT>::IsEmpty() const {
	return m_size == 0;
}

template <typename T, typename UnqualifiedT>
int BidirectionalLinkedList<T, UnqualifiedT>::Size() const {
	return m_size;
}

template <typename T, typename UnqualifiedT>
void BidirectionalLinkedList<T, UnqualifiedT>::PushFront(const T& itm) {
	auto newPtr = std::make_shared<Node<T>>(itm, m_beforeFront, m_beforeFront->next);
	m_beforeFront->next = newPtr;
	if(IsEmpty()) {
		m_afterBack->prev = newPtr;
	} else {
		newPtr->next->prev = newPtr;
	}
	++m_size;
}

template <typename T, typename UnqualifiedT>
void BidirectionalLinkedList<T, UnqualifiedT>::PushBack(const T& itm) {
	auto newPtr = std::make_shared<Node<T>>(itm, m_afterBack->prev, m_afterBack);
	m_afterBack->prev = newPtr;
	if(IsEmpty()) {
		m_beforeFront->next = newPtr;
	} else {
		newPtr->prev->next = newPtr;
	}
	++m_size;
}

template <typename T, typename UnqualifiedT>
void BidirectionalLinkedList<T, UnqualifiedT>::PopFront() {
	PopWhenEmpty();
	--m_size;
	auto deletedNode = m_beforeFront->next;
	m_beforeFront->next = m_beforeFront->next->next;
	m_beforeFront->next->prev = m_beforeFront;
	deletedNode->next = deletedNode->prev = nullptr;
}

template <typename T, typename UnqualifiedT>
void BidirectionalLinkedList<T, UnqualifiedT>::PopBack() {
	PopWhenEmpty();
	--m_size;
	auto deletedNode = m_afterBack->prev;
	m_afterBack->prev = m_afterBack->prev->prev;
	m_afterBack->prev->next = m_afterBack;
	deletedNode->prev = deletedNode->next = nullptr;
}

template <typename T, typename UnqualifiedT>
void BidirectionalLinkedList<T, UnqualifiedT>::PopWhenEmpty() {
	if(IsEmpty()) {
		throw std::runtime_error("Cannot pop element if list is empty");
	}
}



template <typename T, typename UnqualifiedT>
typename BidirectionalLinkedList<T, UnqualifiedT>::iterator BidirectionalLinkedList<T, UnqualifiedT>::begin() const {	
	return iterator(m_beforeFront->next, m_beforeFront, m_afterBack);
}

template <typename T, typename UnqualifiedT>
typename  BidirectionalLinkedList<T, UnqualifiedT>::iterator BidirectionalLinkedList<T, UnqualifiedT>::end() const {
	return iterator(m_afterBack, m_beforeFront, m_afterBack);
}

template <typename T, typename UnqualifiedT>
typename  BidirectionalLinkedList<T, UnqualifiedT>::const_iterator BidirectionalLinkedList<T, UnqualifiedT>::cbegin() const {
	return begin();
}

template <typename T, typename UnqualifiedT>
typename  BidirectionalLinkedList<T, UnqualifiedT>::const_iterator BidirectionalLinkedList<T, UnqualifiedT>::cend() const {
	return end();
}

template <typename T, typename UnqualifiedT>
typename BidirectionalLinkedList<T, UnqualifiedT>::reverse_iterator BidirectionalLinkedList<T, UnqualifiedT>::rbegin() const {
	return std::reverse_iterator<iterator>(end());
}

template <typename T, typename UnqualifiedT>
typename  BidirectionalLinkedList<T, UnqualifiedT>::reverse_iterator BidirectionalLinkedList<T, UnqualifiedT>::rend() const {
	return std::reverse_iterator<iterator>(begin());
}

template <typename T, typename UnqualifiedT>
typename BidirectionalLinkedList<T, UnqualifiedT>::const_reverse_iterator BidirectionalLinkedList<T, UnqualifiedT>::crbegin() const {
	return rbegin();
}

template <typename T, typename UnqualifiedT>
typename  BidirectionalLinkedList<T, UnqualifiedT>::const_reverse_iterator BidirectionalLinkedList<T, UnqualifiedT>::crend() const {
	return rend();
}

