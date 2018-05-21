#pragma once
#include <iterator>
#include <cstddef>
#include <type_traits>
#include <utility>
#include <assert.h>

template <typename Key, typename T> class BinarySearchTreeIt;
template <typename Key, typename T> bool operator==(const BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs);
template <typename Key, typename T> bool operator!=(const BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs);
template <typename Key, typename T> void swap(const  BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs);

template <typename Key, typename T>
class BinarySearchTreeIt {
	friend bool operator== <Key, T>(const BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs);
	friend bool operator!= <Key, T>(const BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs);
	friend void swap<Key, T>(const  BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs);
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = std::pair<Key, T>;
	using difference_type = std::ptrdiff_t;
	using pointer = std::pair<Key, T>*;
	using reference = std::pair<Key, T>&;
	explicit BinarySearchTreeIt(std::shared_ptr<Node<Key, T>> it, 
								std::shared_ptr<Node<Key, T>> bfrMin,
								std::shared_ptr<Node<Key, T>> afrMax);
	std::pair<Key, T>& operator*() const;
	std::pair<Key, T>* operator->() const;
	BinarySearchTreeIt& operator++();
	BinarySearchTreeIt operator++(int);
	BinarySearchTreeIt& operator--();
	BinarySearchTreeIt operator--(int);

private:
	std::shared_ptr<Node<Key, T>> MaxNode() const;
	std::shared_ptr<Node<Key, T>> MinNode() const;

	std::shared_ptr<Node<Key, T>> iter;
	std::shared_ptr<Node<Key, T>> beforeMin;
	std::shared_ptr<Node<Key, T>> afterMax;
};


template <typename Key, typename T>
BinarySearchTreeIt<Key, T>::BinarySearchTreeIt(std::shared_ptr<Node<Key, T>> it,
											   std::shared_ptr<Node<Key, T>> bfrMin,
											   std::shared_ptr<Node<Key, T>> afrMax) 
: iter(it), beforeMin(bfrMin), afterMax(afrMax) {}

template <typename Key, typename T>
std::shared_ptr<Node<Key, T>> BinarySearchTreeIt<Key, T>::MaxNode() const {
	auto node = iter;
	while(node->right != nullptr && node->right != afterMax) {
		node = node->right;
	}
	return node;
}

template <typename Key, typename T>
std::shared_ptr<Node<Key, T>> BinarySearchTreeIt<Key, T>::MinNode() const {
	auto node = iter;
	while(node->left != nullptr && node->left != beforeMin) {
		node = node->left;
	}
	return node;
}

template <typename Key, typename T>
BinarySearchTreeIt<Key, T>& BinarySearchTreeIt<Key, T>::operator++() {
	assert(iter != afterMax);
	if(iter->right != nullptr && iter->right != afterMax) {
		iter = BinarySearchTreeIt<Key, T>(iter->right, beforeMin, afterMax).MinNode();
	} else {
		while(IsParentLeftOfNode(*iter)) {
			iter = iter->parent;
		}
		// set to off-end iterator if there is no parent right of node
		if(!DoesParentExist(*iter)) {
			iter = afterMax;
		// else set to parent on the right
		} else {
			iter = iter->parent;
		}
	}
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
	assert(iter != beforeMin);
	if(iter->left != nullptr && iter->left != beforeMin) {
		iter = BinarySearchTreeIt<Key, T>(iter->left, beforeMin, afterMax).MaxNode();
	} else {
		while(IsParentRightOfNode(*iter)) {
			iter = iter->parent;
		}
		// set to before min iterator if there is no parent left of node
		if(!DoesParentExist(*iter)) {
			iter = beforeMin;
		// else set to parent on the left
		} else {
			iter = iter->parent;
		}
	}
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
	assert(iter != beforeMin && iter != afterMax);
	return iter->value;
}

template <typename Key, typename T>
std::pair<Key, T>* BinarySearchTreeIt<Key, T>::operator->() const {
	return &**this;
}

template <typename Key, typename T>
bool operator==(const BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs) {
	assert(lhs.beforeMin == rhs.beforeMin && lhs.afterMax == rhs.afterMax);
	return lhs.iter == rhs.iter;
}

template <typename Key, typename T>
bool operator!=(const BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs) {
	return !(lhs == rhs);
}

template <typename Key, typename T>
void swap(const  BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs) {
	assert(lhs.beforeMin == rhs.beforeMin && lhs.afterMax == rhs.afterMax);
	using std::swap;
	swap(lhs.iter, rhs.iter);
}