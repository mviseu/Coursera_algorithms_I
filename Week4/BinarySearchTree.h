#pragma once
#include "BinarySearchNode.h"
#include "BinarySearchNodes.h"
#include "BinarySearchTreeIt.h"
#include <functional>
#include <memory>
#include <utility>
#include <iostream>
#include <optional>

namespace {

template <typename Key, typename T>
std::shared_ptr<Node<Key, T>> findAux(const Nodes<Key, T>& nodes,
								   	  const Key& key) {
	if(!DoesRootHaveKey(nodes)) {
		return nodes.afterMax;
	}
	if(key == nodes.root->value.first) {
		return nodes.root;
	}
	if(key < nodes.root->value.first) {
		return findAux(GetLeftNodes(nodes), key);
	}
	return findAux(GetRightNodes(nodes), key);
}

template <typename Key, typename T>
std::optional<std::pair<std::shared_ptr<Node<Key, T>>, bool>>
insertIfFinalNode(std::shared_ptr<Node<Key, T>> parent, const Nodes<Key, T>& nodes, const std::pair<const Key, T>& val) {
	if(nodes.root == nullptr) {
		return std::make_pair(CreateANewNode(val, parent), true);
	}
	if(IsRootTheBeforeMin(nodes)) {
		auto newNodes = nodes;
		newNodes.root = CreateANewMin(val, parent, newNodes.beforeMin);
		LinkBeforeMinParentToRoot(newNodes);
		return std::make_pair(newNodes.root, true);
	}
	if(IsRootTheAfterMax(nodes)) {
		auto newNodes = nodes;
		newNodes.root = CreateANewMax(val, parent, newNodes.afterMax);
		LinkAfterMaxParentToRoot(newNodes);
		return std::make_pair(newNodes.root, true);
	}
	if(val.first == nodes.root->value.first) {
		return std::make_pair(nodes.root, false);
	}
	return std::nullopt;
}


template <typename Key, typename T>
std::pair<std::shared_ptr<Node<Key, T>>, bool> insertAux(std::shared_ptr<Node<Key, T>> parent,
									 					 const Nodes<Key, T>& nodes,
								     					 const std::pair<const Key, T>& val) {
	if(const auto newinsert = insertIfFinalNode(parent, nodes, val)) {
		return *newinsert;
	}
	std::pair<std::shared_ptr<Node<Key, T>>, bool> insertPair = std::make_pair(nullptr, false);
	if(val.first < nodes.root->value.first) {
		insertPair = insertAux(nodes.root, GetLeftNodes(nodes), val);
		nodes.root->left = insertPair.first;
	}
	if(val.first > nodes.root->value.first) {
		insertPair = insertAux(nodes.root, GetRightNodes(nodes), val);
		nodes.root->right = insertPair.first;
	}
	nodes.root->size = GetSizeBasedOnChildren(nodes);
	return std::make_pair(nodes.root, insertPair.second);

}

template <typename Key, typename T>
Nodes<Key, T> EraseWhenRightChildNull(const Nodes<Key, T>& nodes) {
	if(!IsLeftNull(*nodes.root)) {
		nodes.root->left->parent = nodes.root->parent;
	}
	if(IsParentLeftOfNode(*nodes.root)) {
		nodes.root->parent->right = nodes.root->left;
	}
	if(IsParentRightOfNode(*nodes.root)) {
		nodes.root->parent->left = nodes.root->left;
	}
	return GetLeftNodes(nodes);
}

template <typename Key, typename T>
Nodes<Key, T> EraseWhenLeftChildNull(const Nodes<Key, T>& nodes) {
	if(!IsRightNull(*nodes.root)) {
		nodes.root->right->parent = nodes.root->parent;
	}
	if(IsParentLeftOfNode(*nodes.root)) {
		nodes.root->parent->right = nodes.root->right;
	}
	if(IsParentRightOfNode(*nodes.root)) {
		nodes.root->parent->left = nodes.root->right;
	}
	return GetRightNodes(nodes);
}

template <typename Key, typename T>
Nodes<Key, T> eraseAux(const Nodes<Key, T>& nodes, const Key& key);

template <typename Key, typename T>
Nodes<Key, T> ReplaceEraseByMinOnRight(const Nodes<Key, T>& nodes) {
	auto minVal = (MinOfCurrentTree(GetRightNodes(nodes)).root)->value;
	auto successorPair = std::pair<const Key, T>(minVal.first, minVal.second);
	auto treeNoSuccessor = eraseAux(nodes, successorPair.first); 
	auto newNode = std::make_shared<Node<Key, T>>(successorPair, treeNoSuccessor.root->size, treeNoSuccessor.root->parent, treeNoSuccessor.root->left, treeNoSuccessor.root->right);
	PointNodeRelativesToItself(newNode);
	return Nodes<Key, T>(newNode, nodes.beforeMin, nodes.afterMax);
}

template <typename Key, typename T>
Nodes<Key, T> ReplaceEraseByMaxOnLeft(const Nodes<Key, T>& nodes) {
	auto maxVal = (MaxOfCurrentTree(GetLeftNodes(nodes)).root)->value;
	auto successorPair = std::pair<const Key, T>(maxVal);
	auto treeNoSuccessor = eraseAux(nodes, successorPair.first);
	auto newNode = std::make_shared<Node<Key, T>>(successorPair, treeNoSuccessor.root->size, treeNoSuccessor.root->parent, treeNoSuccessor.root->left, treeNoSuccessor.root->right);
	PointNodeRelativesToItself(newNode);
	return Nodes<Key, T>(newNode, treeNoSuccessor.beforeMin, treeNoSuccessor.afterMax);
}

template <typename Key, typename T>
Nodes<Key, T> EraseRoot(const Nodes<Key, T>& nodes) {
	if(IsRootTheOnlyExistingNode(nodes)) {
		nodes.afterMax->parent = nullptr;
		nodes.beforeMin->parent = nullptr;
		nodes.afterMax->left = nodes.beforeMin;
		nodes.beforeMin->right = nodes.afterMax;
		return Nodes<Key, T>(nullptr, nodes.afterMax, nodes.beforeMin);
	}
	if(IsLeftTheBeforeMin(nodes)) {
		return ReplaceEraseByMinOnRight(nodes);
	}
	return ReplaceEraseByMaxOnLeft(nodes);
}

template <typename Key, typename T>
Nodes<Key, T> EraseWhenOneChildIsNull(const Nodes<Key, T>& nodes) {
		// check the size
	if(IsRightNull(*nodes.root)) {
		return EraseWhenRightChildNull(nodes);
	}
	return EraseWhenLeftChildNull(nodes);
}

template <typename Key, typename T>
Nodes<Key, T> EraseCurrentNode(const Nodes<Key, T>& nodes) {
	if(IsTreeAtTheRoot(nodes)) {
		return EraseRoot(nodes);
	}
	if(IsRightNull(*nodes.root) || IsLeftNull(*nodes.root)) {
		return EraseWhenOneChildIsNull(nodes);
	}
	if(IsRightGreater(nodes)) {
		return ReplaceEraseByMinOnRight(nodes);
	}
	if(IsLeftLess(nodes)) {
		return ReplaceEraseByMaxOnLeft(nodes);
	}
	return nodes;	
}

template <typename Key, typename T>
Nodes<Key, T> eraseAux(const Nodes<Key, T>& nodes, const Key& key) {
	// missing: update the size
	assert(DoesRootHaveKey(nodes));
	auto nodeKey = nodes.root->value.first;
	if(nodeKey == key) {
		return EraseCurrentNode(nodes);
	}
	auto nodesNew = nodes;
	if(nodeKey < key) {
		auto rightNodes = eraseAux(GetRightNodes(nodes), key);
		return UpdateRightNodes(nodes, rightNodes);
	}
	auto leftNodes = eraseAux(GetLeftNodes(nodes), key);
	return UpdateLeftNodes(nodes, leftNodes);
}

template <typename Key, typename T>
int RankAux(const Nodes<Key, T>& nodes, const Key& targetKey) {
	if(!DoesRootHaveKey(nodes)) {
		return 0;
	}
	if(nodes.root->value.first == targetKey) {
		return GetSizeOfLeftSubTree(*nodes.root);
	}
	if(nodes.root->value.first < targetKey) {
		return 1 + GetSizeOfLeftSubTree(*nodes.root) + RankAux(GetRightNodes(nodes), targetKey); 
	}
	return RankAux(GetLeftNodes(nodes), targetKey);
}

} // namespace

template <typename Key, typename T>
class BinarySearchTree {
public:
	using iterator = BinarySearchTreeIt<Key, T>;
	using const_iterator = BinarySearchTreeIt<Key, const T>;
	using value_type = std::pair<const  Key, T>;
	BinarySearchTree() = default;
	BinarySearchTree(const BinarySearchTree&);
	BinarySearchTree(BinarySearchTree&&);
	BinarySearchTree&operator=(const BinarySearchTree&) = delete;
	BinarySearchTree&operator=(BinarySearchTree&&) = delete;
	iterator find(const Key& key); // see how to get const_iterator
	std::pair<iterator, bool> insert(const value_type& val);
	iterator erase(iterator pos);
	bool empty() const;
	int Rank(const Key& targetKey) const;
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;
	iterator begin();
	iterator end();

private:
	Nodes<Key, T> m_nodes;
};

template <typename Key, typename T>
bool BinarySearchTree<Key, T>::empty() const {
	return m_nodes.root == nullptr;
}

template<typename Key, typename T>
typename BinarySearchTree<Key, T>::iterator BinarySearchTree<Key, T>::find(const Key& key) {
	auto findNode = findAux(m_nodes, key);
	return iterator(Nodes<Key, T>(findNode, m_nodes.beforeMin, m_nodes.afterMax));

}

template<typename Key, typename T>
std::pair<typename BinarySearchTree<Key, T>::iterator, bool> BinarySearchTree<Key, T>::insert(const value_type& val) {
	if(empty()) {
		m_nodes.root = CreateANewTree(val, m_nodes.beforeMin, m_nodes.afterMax);
		m_nodes.beforeMin->parent = m_nodes.root;
		m_nodes.afterMax->parent = m_nodes.root;
		return std::make_pair(find(val.first), true);
	}
	auto insertPair = insertAux(m_nodes.root->parent, m_nodes, val);
	return std::make_pair(find(val.first), insertPair.second);

}

template<typename Key, typename T>
typename BinarySearchTree<Key, T>::iterator BinarySearchTree<Key, T>::erase(iterator pos) {
	if(pos == end()) {
		return end();
	}
	auto key = pos->first;
	auto findNode = findAux(m_nodes, key);
	std::optional<Key> nextKey;
	auto itNext = ++iterator(Nodes<Key, T>(findNode, m_nodes.beforeMin, m_nodes.afterMax));
	if(itNext != end()) {
		nextKey = itNext->first;
	}
	m_nodes = eraseAux(m_nodes, key);
	auto findnext = find(*nextKey);
	return nextKey ? findnext : end();
}

//Rank -> how many keys < target key?
template<typename Key, typename T>
int BinarySearchTree<Key, T>::Rank(const Key& targetKey) const {
	return RankAux(m_nodes, targetKey);
}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::iterator BinarySearchTree<Key, T>::begin() {
	if(empty()) {
		return end();
	}
	return iterator(Min(m_nodes));
}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::iterator BinarySearchTree<Key, T>::end() {
	return iterator(GetAfterMaxNodes(m_nodes));
}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::const_iterator BinarySearchTree<Key, T>::begin() const {
	return const_iterator((const_cast<BinarySearchTree<Key, T>&>(*this).begin()));
}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::const_iterator BinarySearchTree<Key, T>::end() const {
	return const_iterator((const_cast<BinarySearchTree<Key, T>&>(*this).end()));
}


template <typename Key, typename T>
typename BinarySearchTree<Key, T>::const_iterator BinarySearchTree<Key, T>::cbegin() const {
	return begin();
}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::const_iterator BinarySearchTree<Key, T>::cend() const {
	return end();
}

/* copy constructors need to be defined */
/*
To do - have non-const and a const version of find
To do iterator - const/non const versions
To do - progress with ordered op: mix, max, ceiling, floor, iteration?
copy control
*/