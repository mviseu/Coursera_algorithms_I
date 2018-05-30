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
	nodes.root->size = GetSizeBasedOnChildren(*nodes.root);
	return std::make_pair(nodes.root, insertPair.second);

}

template <typename Key, typename T>
void EraseWhenRightChildNull(Node<Key, T>& eraseNode) {
	if(!IsLeftNull(eraseNode)) {
		eraseNode.left->parent = eraseNode.parent;
	}
	if(IsParentLeftOfNode(eraseNode)) {
		eraseNode.parent->right = eraseNode.left;
	}
	if(IsParentRightOfNode(eraseNode)) {
		eraseNode.parent->left = eraseNode.left;
	}
	eraseNode.parent = nullptr;
	eraseNode.left = nullptr;
	eraseNode.right = nullptr;
}

template <typename Key, typename T>
void EraseWhenLeftChildNull(Node<Key, T>& eraseNode) {
	if(!IsRightNull(eraseNode)) {
		eraseNode.right->parent = eraseNode.parent;
	}
	if(IsParentLeftOfNode(eraseNode)) {
		eraseNode.parent->right = eraseNode.right;
	}
	if(IsParentRightOfNode(eraseNode)) {
		eraseNode.parent->left = eraseNode.right;
	}
	eraseNode.parent = nullptr;
	eraseNode.left = nullptr;
	eraseNode.right = nullptr;
}

template <typename Key, typename T>
void MakeChildrenPointToNode(std::shared_ptr<Node<Key, T>> node) {
	if(!IsLeftNull(*node)) {
		node->left->parent = node;
	}
	if(!IsRightNull(*node)) {
		node->right->parent = node;
	}
}

template <typename Key, typename T>
void MakeLeftParentPointToNode(std::shared_ptr<Node<Key, T>> node) {
	if(!IsParentNull(*node)) {
		node->parent->right = node;
	}
}

template <typename Key, typename T>
void MakeRightParentPointToNode(std::shared_ptr<Node<Key, T>> node) {
	if(!IsParentNull(*node)) {
		node->parent->left = node;
	}
}

template <typename Key, typename T>
void eraseAux(Nodes<Key, T>& nodes,
			  const Key& key);

template <typename Key, typename T>
void ReplaceEraseByMinOnRight(Nodes<Key, T>& eraseNodes) {
	auto minVal = (MinOfCurrentTree(GetRightNodes(eraseNodes)).root)->value;
	auto successorPair = std::pair<const Key, T>(minVal.first, minVal.second);
	eraseAux(eraseNodes, successorPair.first);
	auto newNode = std::make_shared<Node<Key, T>>(successorPair, eraseNodes.root->size, eraseNodes.root->parent, eraseNodes.root->left, eraseNodes.root->right);
	MakeChildrenPointToNode(newNode);
	MakeLeftParentPointToNode(newNode);
	eraseNodes = Nodes<Key, T>(newNode, eraseNodes.beforeMin, eraseNodes.afterMax);
}

template <typename Key, typename T>
void ReplaceEraseByMaxOnLeft(Nodes<Key, T>& eraseNodes) {
	auto maxVal = (MaxOfCurrentTree(GetLeftNodes(eraseNodes)).root)->value;
	auto successorPair = std::pair<const Key, T>(maxVal);
	eraseAux(eraseNodes, successorPair.first);
	auto newNode = std::make_shared<Node<Key, T>>(successorPair, eraseNodes.root->size, eraseNodes.root->parent, eraseNodes.root->left, eraseNodes.root->right);
	MakeChildrenPointToNode(newNode);
	MakeRightParentPointToNode(newNode);
	eraseNodes = Nodes<Key, T>(newNode, eraseNodes.beforeMin, eraseNodes.afterMax);
}

template <typename Key, typename T>
bool IsEraseNodeTheRoot(const Nodes<Key, T>& treeWithRoot, std::shared_ptr<Node<Key, T>> eraseNode) {
	return treeWithRoot.root == eraseNode;
}

template <typename Key, typename T>
void EraseRoot(Nodes<Key, T>& nodes) {
	if(IsRootTheOnlyExistingNode(nodes)) {
		nodes.afterMax->parent = nullptr;
		nodes.beforeMin->parent = nullptr;
		nodes.afterMax->left = nodes.beforeMin;
		nodes.beforeMin->right = nodes.afterMax;
		nodes = Nodes<Key, T>(nullptr, nodes.afterMax, nodes.beforeMin);
		return;
	}
	if(IsLeftTheBeforeMin(nodes)) {
		ReplaceEraseByMinOnRight(nodes);
		return;
	}
	ReplaceEraseByMaxOnLeft(nodes);
	return;
}

template <typename Key, typename T>
void EraseWhenOneChildIsNull(Node<Key, T>& eraseNode) {
		// check the size
	if(IsRightNull(eraseNode)) {
		EraseWhenRightChildNull(eraseNode);
		return;
	}
	EraseWhenLeftChildNull(eraseNode);
	return;
}

template <typename Key, typename T>
void eraseAux(Nodes<Key, T>& nodes,
			  const Key& key) {
	// missing: update the size
	auto eraseNode = findAux(nodes, key);
	if(IsEraseNodeTheRoot(nodes, eraseNode)) {
		EraseRoot(nodes);
		return;
	}
	if(IsRightNull(*eraseNode) || IsLeftNull(*eraseNode)) {
		EraseWhenOneChildIsNull(*eraseNode);
		return;
	}
	auto eraseNodes = Nodes<Key, T>(eraseNode, nodes.beforeMin, nodes.afterMax);
	if(IsRightGreater(eraseNodes)) {
		ReplaceEraseByMinOnRight(eraseNodes);
		return;
	}
	if(IsLeftLess(eraseNodes)) {
		ReplaceEraseByMaxOnLeft(eraseNodes);
		return;
	}
	return;
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
	auto findNode = findAux(m_nodes, pos->first);
	std::optional<Key> nextKey;
	auto itNext = ++iterator(Nodes<Key, T>(findNode, m_nodes.beforeMin, m_nodes.afterMax));
	if(itNext != end()) {
		nextKey = itNext->first;
	}
	eraseAux(m_nodes, pos->first);
	auto findnext = find(*nextKey);
	return nextKey ? findnext : end(); 
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