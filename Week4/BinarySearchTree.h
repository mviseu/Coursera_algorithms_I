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
std::shared_ptr<Node<Key, T>> FindAux(const Nodes<Key, T>& nodes,
								   	  const std::pair<const Key, T>& val) {
	if(!DoesRootHaveKey(nodes)) {
		return nodes.afterMax;
	}
	if(val.first == nodes.root->value.first) {
		return nodes.root;
	}
	if(val.first < nodes.root->value.first) {
		return FindAux(GetLeftNodes(nodes), val);
	}
	return FindAux(GetRightNodes(nodes), val);
}

template <typename Key, typename T>
std::optional<std::pair<std::shared_ptr<Node<Key, T>>, bool>>
InsertIfFinalNode(std::shared_ptr<Node<Key, T>> parent, Nodes<Key, T> nodes, const std::pair<const Key, T>& val) {
	if(nodes.root == nullptr) {
		nodes.root = CreateANewNode(val, parent);
		return std::make_pair(nodes.root, true);
	}
	if(IsRootTheBeforeMin(nodes)) {
		nodes.root = CreateANewMin(val, parent, nodes.beforeMin);
		LinkBeforeMinParentToRoot(nodes);
		return std::make_pair(nodes.root, true);
	}
	if(IsRootTheAfterMax(nodes)) {
		nodes.root = CreateANewMax(val, parent, nodes.afterMax);
		LinkAfterMaxParentToRoot(nodes);
		return std::make_pair(nodes.root, true);
	}
	if(val.first == nodes.root->value.first) {
		return std::make_pair(nodes.root, false);
	}
	return std::nullopt;
}


template <typename Key, typename T>
std::pair<std::shared_ptr<Node<Key, T>>, bool> InsertAux(std::shared_ptr<Node<Key, T>> parent,
									 					 Nodes<Key, T> nodes,
								     					 const std::pair<const Key, T>& val) {
	if(const auto newInsert = InsertIfFinalNode(parent, nodes, val)) {
		return *newInsert;
	}
	std::pair<std::shared_ptr<Node<Key, T>>, bool> insertPair = std::make_pair(nullptr, false);
	if(val.first < nodes.root->value.first) {
		insertPair = InsertAux(nodes.root, GetLeftNodes(nodes), val);
		nodes.root->left = insertPair.first;
	}
	if(val.first > nodes.root->value.first) {
		insertPair = InsertAux(nodes.root, GetRightNodes(nodes), val);
		nodes.root->right = insertPair.first;
	}
	nodes.root->size = GetSizeBasedOnChildren(*nodes.root);
	return std::make_pair(nodes.root, insertPair.second);

}

} // namespace

template <typename Key, typename T>
class BinarySearchTree {
public:
	using iterator = BinarySearchTreeIt<Key, T>;
	using const_iterator = BinarySearchTreeIt<Key, const T>;
	using value_type = typename iterator::value_type;
	BinarySearchTree() = default;
	iterator Find(const value_type& val); // see how to get const_iterator
	std::pair<iterator, bool> Insert(const value_type& val);
	bool Empty() const;
	const_iterator Begin() const;
	const_iterator End() const;
	const_iterator CBegin() const;
	const_iterator CEnd() const;
	iterator Begin();
	iterator End();

private:
	Nodes<Key, T> nodes;
};

template <typename Key, typename T>
bool BinarySearchTree<Key, T>::Empty() const {
	return nodes.root == nullptr;
}

template<typename Key, typename T>
typename BinarySearchTree<Key, T>::iterator BinarySearchTree<Key, T>::Find(const value_type& val) {
	auto findNode = FindAux(nodes, val);
	auto it = iterator(Nodes<Key, T>(findNode, nodes.beforeMin, nodes.afterMax));
	return it;

}

template<typename Key, typename T>
std::pair<typename BinarySearchTree<Key, T>::iterator, bool> BinarySearchTree<Key, T>::Insert(const value_type& val) {
	if(Empty()) {
		nodes.root = CreateANewTree(val, nodes.beforeMin, nodes.afterMax);
		nodes.beforeMin->parent = nodes.root;
		nodes.afterMax->parent = nodes.root;
		return std::make_pair(Find(val), true);
	}
	auto insertPair = InsertAux(nodes.root->parent, nodes, val);
	return std::make_pair(Find(val), insertPair.second);

}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::iterator BinarySearchTree<Key, T>::Begin() {
	return iterator(Min(nodes));
}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::iterator BinarySearchTree<Key, T>::End() {
	return iterator(GetAfterMaxNodes(nodes));
}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::const_iterator BinarySearchTree<Key, T>::Begin() const {
	return const_iterator((const_cast<BinarySearchTree<Key, T>&>(*this).Begin()));
}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::const_iterator BinarySearchTree<Key, T>::End() const {
	return const_iterator((const_cast<BinarySearchTree<Key, T>&>(*this).End()));
}


template <typename Key, typename T>
typename BinarySearchTree<Key, T>::const_iterator BinarySearchTree<Key, T>::CBegin() const {
	return Begin();
}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::const_iterator BinarySearchTree<Key, T>::CEnd() const {
	return End();
}

/* copy constructors need to be defined */
/*
To do - have non-const and a const version of find
To do iterator - const/non const versions
To do - progress with ordered op: mix, max, ceiling, floor, iteration?
*/