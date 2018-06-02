#pragma once
#include "BinarySearchNodes.h"
#include <iterator>
#include <cstddef>
#include <type_traits>
#include <utility>
#include <assert.h>
#include <iostream>

template <typename Key, typename T, typename UnqualifiedT> class BinarySearchTreeIt;
template <typename Key, typename T, typename UnqualifiedT> bool operator==(const BinarySearchTreeIt<Key, T, UnqualifiedT>& lhs, const BinarySearchTreeIt<Key, T, UnqualifiedT>& rhs);
template <typename Key, typename T, typename UnqualifiedT> bool operator!=(const BinarySearchTreeIt<Key, T, UnqualifiedT>& lhs, const BinarySearchTreeIt<Key, T, UnqualifiedT>& rhs);
template <typename Key, typename T, typename UnqualifiedT> void swap(const  BinarySearchTreeIt<Key, T, UnqualifiedT>& lhs, const BinarySearchTreeIt<Key, T, UnqualifiedT>& rhs);

template <typename Key, typename T, typename UnqualifiedT = std::remove_cv_t<T>>
class BinarySearchTreeIt {
	friend bool operator== <Key, T, UnqualifiedT>(const BinarySearchTreeIt<Key, T, UnqualifiedT>& lhs, const BinarySearchTreeIt<Key, T, UnqualifiedT>& rhs);
	friend bool operator!= <Key, T, UnqualifiedT>(const BinarySearchTreeIt<Key, T, UnqualifiedT>& lhs, const BinarySearchTreeIt<Key, T, UnqualifiedT>& rhs);
	friend void swap<Key, T, UnqualifiedT>(const BinarySearchTreeIt<Key, T, UnqualifiedT>& lhs, const BinarySearchTreeIt<Key, T, UnqualifiedT>& rhs);
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = std::pair<const Key, T>;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;
	explicit BinarySearchTreeIt(const Nodes<Key, UnqualifiedT>& nodes);
	operator BinarySearchTreeIt<Key, const T>() {return BinarySearchTreeIt<Key, const T>(m_nodes);}
	reference operator*();
	pointer operator->();
	BinarySearchTreeIt<Key, T, UnqualifiedT>& operator++();
	BinarySearchTreeIt<Key, T, UnqualifiedT> operator++(int);
	BinarySearchTreeIt<Key, T, UnqualifiedT>& operator--();
	BinarySearchTreeIt<Key, T, UnqualifiedT> operator--(int);

private:
	Nodes<Key, UnqualifiedT> m_nodes;
};


template <typename Key, typename T, typename UnqualifiedT>
BinarySearchTreeIt<Key, T, UnqualifiedT>::BinarySearchTreeIt(const Nodes<Key, UnqualifiedT>& nodes) 
: m_nodes(nodes) {}

template <typename Key, typename T, typename UnqualifiedT>
BinarySearchTreeIt<Key, T, UnqualifiedT>& BinarySearchTreeIt<Key, T, UnqualifiedT>::operator++() {
	assert(!IsRootTheAfterMax(m_nodes));
	if(IsRightGreater(m_nodes)) {
		m_nodes = MinOfCurrentTree(GetRightNodes(m_nodes));
	} else {
		while(IsParentLeftOfNode(*m_nodes.root)) {
			m_nodes = GetParentNodes(m_nodes);
		}
		// set to off-end iterator if there is no parent right of node
		if(!DoesParentExist(*m_nodes.root)) {
			m_nodes = GetAfterMaxNodes(m_nodes);
		// else set to parent on the right
		} else {
			m_nodes = GetParentNodes(m_nodes);
		}
	}
	return *this;
}

template <typename Key, typename T, typename UnqualifiedT>
BinarySearchTreeIt<Key, T, UnqualifiedT> BinarySearchTreeIt<Key, T, UnqualifiedT>::operator++(int) {
	auto oldThis = *this;
	++*this;
	return oldThis;
}

template <typename Key, typename T, typename UnqualifiedT>
BinarySearchTreeIt<Key, T, UnqualifiedT>& BinarySearchTreeIt<Key, T, UnqualifiedT>::operator--() {
	assert(!IsRootTheBeforeMin(m_nodes));
	if(IsLeftLess(m_nodes)) {
		m_nodes = MaxOfCurrentTree(GetLeftNodes(m_nodes));
	} else {
		while(IsParentRightOfNode(*m_nodes.root)) {
			m_nodes = GetParentNodes(m_nodes);
		}
		// set to before min iterator if there is no parent left of node
		if(!DoesParentExist(*m_nodes.root)) {
			m_nodes = GetBeforeMinNodes(m_nodes);
		// else set to parent on the left
		} else {
			m_nodes = GetParentNodes(m_nodes);
		}
	}
	return *this;
}

template <typename Key, typename T, typename UnqualifiedT>
BinarySearchTreeIt<Key, T, UnqualifiedT> BinarySearchTreeIt<Key, T, UnqualifiedT>::operator--(int) {
	auto oldThis = *this;
	--*this;
	return oldThis;
}

template <typename Key, typename T, typename UnqualifiedT>
typename BinarySearchTreeIt<Key, T, UnqualifiedT>::reference BinarySearchTreeIt<Key, T, UnqualifiedT>::operator*() {
	assert(DoesRootHaveKey(m_nodes));
	return m_nodes.root->value;
}

template <typename Key, typename T, typename UnqualifiedT>
typename BinarySearchTreeIt<Key, T, UnqualifiedT>::pointer BinarySearchTreeIt<Key, T, UnqualifiedT>::operator->() {
	return &**this;
}

template <typename Key, typename T, typename UnqualifiedT>
bool operator==(const BinarySearchTreeIt<Key, T, UnqualifiedT>& lhs, const BinarySearchTreeIt<Key, T, UnqualifiedT>& rhs) {
	assert(AreNonKeyValuesTheSame(lhs.m_nodes, rhs.m_nodes));
	return lhs.m_nodes.root == rhs.m_nodes.root;
}

template <typename Key, typename T, typename UnqualifiedT>
bool operator!=(const BinarySearchTreeIt<Key, T, UnqualifiedT>& lhs, const BinarySearchTreeIt<Key, T, UnqualifiedT>& rhs) {
	return !(lhs == rhs);
}

template <typename Key, typename T, typename UnqualifiedT>
void swap(const  BinarySearchTreeIt<Key, T, UnqualifiedT>& lhs, const BinarySearchTreeIt<Key, T, UnqualifiedT>& rhs) {
	assert(AreNonKeyValuesTheSame(lhs.m_nodes, rhs.m_nodes));
	using std::swap;
	swap(lhs.m_nodes.root, rhs.m_nodes.root);
}