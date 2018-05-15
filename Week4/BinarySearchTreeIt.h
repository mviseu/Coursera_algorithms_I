#pragma once
#include "BinarySearchNode.h"
#include <iterator>
#include <cstddef>
#include <type_traits>
#include <utility>
#include <assert.h>

template <typename Key, typename T> class BinarySearchTreeIt;
template <typename Key, typename T> bool operator==(const BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs);
template <typename Key, typename T> bool operator!=(const BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs);

template <typename Key, typename T>
class BinarySearchTreeIt {
	friend bool operator== <Key, T>(const BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs);
	friend bool operator!= <Key, T>(const BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs);
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = std::pair<Key, T>;
	using difference_type = std::ptrdiff_t;
	using pointer = std::pair<Key, T>*;
	using reference = std::pair<Key, T>&;
	explicit BinarySearchTreeIt(const std::shared_ptr<Node<Key, T>>& it, const std::shared_ptr<Node<Key, T>>& bfrnt, const std::shared_ptr<Node<Key, T>>& aftbck);
	std::pair<Key, T>& operator*() const;
	std::pair<Key, T>* operator->() const;
	BinarySearchTreeIt& operator++();
	BinarySearchTreeIt operator++(int);
	BinarySearchTreeIt& operator--();
	BinarySearchTreeIt operator--(int);

private:
	std::shared_ptr<Node<Key, T>> iterator;
	std::shared_ptr<Node<Key, T>> beforeFront;
	std::shared_ptr<Node<Key, T>> afterBack;
};

template <typename Key, typename T>
BinarySearchTreeIt<Key, T>::BinarySearchTreeIt(const std::shared_ptr<Node<Key, T>>& it, const std::shared_ptr<Node<Key, T>>& bfrnt, const std::shared_ptr<Node<Key, T>>& aftbck) 
: iterator(it), beforeFront(bfrnt), afterBack(aftbck) {}

template <typename Key, typename T>
BinarySearchTreeIt<Key, T>& BinarySearchTreeIt<Key, T>::operator++() {
	assert(iterator != afterBack);
	iterator = iterator->right;
	return *this;
}

template <typename Key, typename T>
BinarySearchTreeIt<Key, T> BinarySearchTreeIt<Key, T>::operator++(int) {
	auto oldThis = *this;
	++*this;
	return oldThis;
}

template <typename Key, typename T>
BinarySearchTreeIt<Key, T>& BinarySearchTreeIt<Key, T>::operator--() {
	assert(iterator != beforeFront);
	iterator = iterator->left;
	return *this;
}

template <typename Key, typename T>
BinarySearchTreeIt<Key, T> BinarySearchTreeIt<Key, T>::operator--(int) {
	auto oldThis = *this;
	--*this;
	return oldThis;
}

template <typename Key, typename T>
std::pair<Key, T>& BinarySearchTreeIt<Key, T>::operator*() const {
	assert(iterator != beforeFront && iterator != afterBack);
	return iterator->value;
}

template <typename Key, typename T>
std::pair<Key, T>* BinarySearchTreeIt<Key, T>::operator->() const {
	return &**this;
}

template <typename Key, typename T>
bool operator!=(const BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs) {
	!(lhs == rhs); // if iterators are same, beforeFront and afterBack should also be same
}