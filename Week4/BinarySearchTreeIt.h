#pragma once
#include "BinarySearchNodes.h"
#include <iterator>
#include <cstddef>
#include <utility>
#include <assert.h>
#include <iostream>

template <typename Key, typename T> class BinarySearchTreeIt;
template <typename Key, typename T> bool operator==(const BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs);
template <typename Key, typename T> bool operator!=(const BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs);
template <typename Key, typename T> void swap(const  BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs);

template <typename Key, typename T>
class BinarySearchTreeIt {
	friend bool operator== <Key, T>(const BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs);
	friend bool operator!= <Key, T>(const BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs);
	friend void swap<Key, T>(const BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs);
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = std::pair<const Key, T>;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;
	explicit BinarySearchTreeIt(const Nodes<Key, T>& nodes);
	reference operator*();
	pointer operator->();
	BinarySearchTreeIt<Key, T>& operator++();
	BinarySearchTreeIt<Key, T> operator++(int);
	BinarySearchTreeIt<Key, T>& operator--();
	BinarySearchTreeIt<Key, T> operator--(int);

private:
	Nodes<Key, T> m_nodes;
};


template <typename Key, typename T>
BinarySearchTreeIt<Key, T>::BinarySearchTreeIt(const Nodes<Key, T>& nodes) 
: m_nodes(nodes) {}

template <typename Key, typename T>
BinarySearchTreeIt<Key, T>& BinarySearchTreeIt<Key, T>::operator++() {
	assert(!IsRootTheAfterMax(m_nodes));
	if(IsRightGreater(m_nodes)) {
		m_nodes = MinOfCurrentTree(GetRightNodes(m_nodes));
	} else {
		while(IsParentLeftOfNode(*m_nodes.node)) {
			m_nodes = GetParentNodes(m_nodes);
		}
		// set to off-end iterator if there is no parent right of node
		if(!DoesParentExist(*m_nodes.node)) {
			m_nodes = GetAfterMaxNodes(m_nodes);
		// else set to parent on the right
		} else {
			m_nodes = GetParentNodes(m_nodes);
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
	assert(!IsRootTheBeforeMin(m_nodes));
	if(IsLeftLess(m_nodes)) {
		m_nodes = MaxOfCurrentTree(GetLeftNodes(m_nodes));
	} else {
		while(IsParentRightOfNode(*m_nodes.node)) {
			m_nodes = GetParentNodes(m_nodes);
		}
		// set to before min iterator if there is no parent left of node
		if(!DoesParentExist(*m_nodes.node)) {
			m_nodes = GetBeforeMinNodes(m_nodes);
		// else set to parent on the left
		} else {
			m_nodes = GetParentNodes(m_nodes);
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
typename BinarySearchTreeIt<Key, T>::reference BinarySearchTreeIt<Key, T>::operator*() {
	assert(DoesRootHaveKey(m_nodes));
	return m_nodes.node->value;
}

template <typename Key, typename T>
typename BinarySearchTreeIt<Key, T>::pointer BinarySearchTreeIt<Key, T>::operator->() {
	return &**this;
}

template <typename Key, typename T>
bool operator==(const BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs) {
	assert(AreNonKeyValuesTheSame(lhs.m_nodes, rhs.m_nodes));
	return lhs.m_nodes.node == rhs.m_nodes.node;
}

template <typename Key, typename T>
bool operator!=(const BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs) {
	return !(lhs == rhs);
}

template <typename Key, typename T>
void swap(const  BinarySearchTreeIt<Key, T>& lhs, const BinarySearchTreeIt<Key, T>& rhs) {
	assert(AreNonKeyValuesTheSame(lhs.m_nodes, rhs.m_nodes));
	using std::swap;
	swap(lhs.m_nodes.node, rhs.m_nodes.node);
}