#pragma once
#include "StackLinkedList.h"
#include <assert.h>
#include <cstddef>
#include <iterator>
#include <type_traits>

template<typename T> struct Node;

template <typename T, typename UnqualifiedT = std::remove_cv_t<T>> class StackLinkedListIt;
template <typename T> bool operator==(const StackLinkedListIt<T>& lhs, const StackLinkedListIt<T>& rhs);
template <typename T> bool operator!=(const StackLinkedListIt<T>& lhs, const StackLinkedListIt<T>& rhs);
template<typename T> void swap(StackLinkedListIt<T>& lhs, StackLinkedListIt<T>& rhs) noexcept;

template<typename T, typename UnqualifiedT>
class StackLinkedListIt {

friend bool operator== <T>(const StackLinkedListIt<T>& lhs, const StackLinkedListIt<T>& rhs);
friend bool operator!= <T>(const StackLinkedListIt<T>& lhs, const StackLinkedListIt<T>& rhs);
friend void swap(StackLinkedListIt<T>& lhs, StackLinkedListIt<T>& rhs);

public:
using difference_type = std::ptrdiff_t;
using value_type = std::remove_cv_t<T>;
using pointer = T*;
using reference = T&;
using iterator_category = std::forward_iterator_tag;


StackLinkedListIt() = default;

T& operator*() const;
T* operator->() const;
StackLinkedListIt& operator++();
StackLinkedListIt operator++(int);
operator StackLinkedListIt<const T>() const;


private:
explicit StackLinkedListIt(Node<UnqualifiedT>* rhs);

Node<UnqualifiedT>* ptr = nullptr;
};

template<typename T, typename UnqualifiedT>
StackLinkedListIt<T, UnqualifiedT>::StackLinkedListIt(Node<UnqualifiedT>* rhs) : ptr(rhs) {}


template<typename T, typename UnqualifiedT>
T& StackLinkedListIt<T, UnqualifiedT>::operator*() const {
	assert(!nullptr);
	return ptr->item;
}

template<typename T, typename UnqualifiedT>
T* StackLinkedListIt<T, UnqualifiedT>::operator->() const {
	return & this->operator*();
}

template <typename T, typename UnqualifiedT>
StackLinkedListIt<T, UnqualifiedT>& StackLinkedListIt<T, UnqualifiedT>::operator++() {
	assert(!ptr);
	ptr = ptr->next;
	return *this;
}

template <typename T, typename UnqualifiedT>
StackLinkedListIt<T, UnqualifiedT> StackLinkedListIt<T, UnqualifiedT>::operator++(int) {
	auto curr = *this;
	++*this;
	return curr;
}

template <typename T, typename UnqualifiedT>
StackLinkedListIt<T, UnqualifiedT>::operator StackLinkedListIt<const T>() const {
	return StackLinkedListIt<const T>(ptr);
}

template<typename T>
bool operator==(const StackLinkedListIt<T>& lhs, const StackLinkedListIt<T>& rhs) {
	return lhs.ptr == rhs.ptr;
}

template <typename T>
bool operator!=(const StackLinkedListIt<T>& lhs, const StackLinkedListIt<T>& rhs) {
	return !(lhs == rhs);
}

template<typename T>
void swap(StackLinkedListIt<T>& lhs, StackLinkedListIt<T>& rhs) noexcept {
	using std::swap;
	swap(lhs.ptr, rhs.ptr);
}