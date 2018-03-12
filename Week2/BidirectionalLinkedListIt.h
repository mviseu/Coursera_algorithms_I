#pragma once
#include "BidirectionalLinkedList.h"
#include <assert.h>
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <memory>
#include <iostream>

template<typename T> struct Node;

template <typename T, typename UnqualifiedT = std::remove_cv_t<T>> class BidirectionalLinkedListIt;
template <typename T> bool operator==(const BidirectionalLinkedListIt<T>& lhs, const BidirectionalLinkedListIt<T>& rhs);
template <typename T> bool operator!=(const BidirectionalLinkedListIt<T>& lhs, const BidirectionalLinkedListIt<T>& rhs);
template <typename T> void swap(BidirectionalLinkedListIt<T>& lhs, BidirectionalLinkedListIt<T>& rhs) noexcept;

template<typename T, typename UnqualifiedT>
class BidirectionalLinkedListIt {

friend bool operator== <T>(const BidirectionalLinkedListIt<T>& lhs, const BidirectionalLinkedListIt<T>& rhs);
friend bool operator!= <T>(const BidirectionalLinkedListIt<T>& lhs, const BidirectionalLinkedListIt<T>& rhs);
friend void swap<T>(BidirectionalLinkedListIt<T>& lhs, BidirectionalLinkedListIt<T>& rhs) noexcept;

public:
using difference_type = std::ptrdiff_t;
using value_type = std::remove_cv_t<T>;
using pointer = T*;
using reference = T&;
using iterator_category = std::bidirectional_iterator_tag;

explicit BidirectionalLinkedListIt(std::shared_ptr<Node<UnqualifiedT>> pr,
								   std::shared_ptr<Node<UnqualifiedT>> beforeFr,
								   std::shared_ptr<Node<UnqualifiedT>> afterBk); 
BidirectionalLinkedListIt() = default;

T& operator*() const;
T* operator->() const;
BidirectionalLinkedListIt& operator++();
BidirectionalLinkedListIt operator++(int);
BidirectionalLinkedListIt& operator--();
BidirectionalLinkedListIt operator--(int);
operator BidirectionalLinkedListIt<const T>() const;


private:
std::shared_ptr<Node<UnqualifiedT>> ptr = nullptr;
std::shared_ptr<Node<UnqualifiedT>> beforeFront = nullptr;
std::shared_ptr<Node<UnqualifiedT>> afterBack = nullptr;
};

template<typename T, typename UnqualifiedT>
BidirectionalLinkedListIt<T, UnqualifiedT>::BidirectionalLinkedListIt(std::shared_ptr<Node<UnqualifiedT>> pr,
								   									  std::shared_ptr<Node<UnqualifiedT>> beforeFr,
								   									  std::shared_ptr<Node<UnqualifiedT>> afterBk)
: ptr(pr), beforeFront(beforeFr), afterBack(afterBk) {}

template<typename T, typename UnqualifiedT>
T& BidirectionalLinkedListIt<T, UnqualifiedT>::operator*() const {
	assert(ptr != beforeFront && ptr != afterBack);
	return ptr->item;
}

template<typename T, typename UnqualifiedT>
T* BidirectionalLinkedListIt<T, UnqualifiedT>::operator->() const {
	return & this->operator*();
}

template <typename T, typename UnqualifiedT>
BidirectionalLinkedListIt<T, UnqualifiedT>& BidirectionalLinkedListIt<T, UnqualifiedT>::operator++() {
	assert(ptr != afterBack);
	ptr = ptr->next;
	return *this;
}

template <typename T, typename UnqualifiedT>
BidirectionalLinkedListIt<T, UnqualifiedT> BidirectionalLinkedListIt<T, UnqualifiedT>::operator++(int) {
	auto curr = *this;
	++*this;
	return curr;
}


template <typename T, typename UnqualifiedT>
BidirectionalLinkedListIt<T, UnqualifiedT>& BidirectionalLinkedListIt<T, UnqualifiedT>::operator--() {
	assert(ptr != beforeFront);
	ptr = ptr->prev;
	return *this;
}

template <typename T, typename UnqualifiedT>
BidirectionalLinkedListIt<T, UnqualifiedT> BidirectionalLinkedListIt<T, UnqualifiedT>::operator--(int) {
	auto curr = *this;
	--*this;
	return curr;
}

template <typename T, typename UnqualifiedT>
BidirectionalLinkedListIt<T, UnqualifiedT>::operator BidirectionalLinkedListIt<const T>() const {
	return BidirectionalLinkedListIt<const T>(ptr, beforeFront, afterBack);
}

template<typename T>
bool operator==(const BidirectionalLinkedListIt<T>& lhs, const BidirectionalLinkedListIt<T>& rhs) {
	assert(lhs.beforeFront == rhs.beforeFront && lhs.afterBack == rhs.afterBack);
	return lhs.ptr == rhs.ptr;
}

template <typename T>
bool operator!=(const BidirectionalLinkedListIt<T>& lhs, const BidirectionalLinkedListIt<T>& rhs) {
	return !(lhs == rhs);
}

template<typename T>
void swap(BidirectionalLinkedListIt<T>& lhs, BidirectionalLinkedListIt<T>& rhs) noexcept {
	assert(lhs.beforeFront == rhs.beforeFront && lhs.afterBack == rhs.afterBack);
	using std::swap;
	swap(lhs.ptr, rhs.ptr);
}