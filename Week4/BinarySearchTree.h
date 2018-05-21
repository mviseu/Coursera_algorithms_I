#pragma once
#include "BinarySearchNode.h"
#include "BinarySearchTreeIt.h"
#include <functional>
#include <memory>
#include <utility>

namespace {

template <typename Key, typename T>
std::shared_ptr<Node<Key, T>> FindAux(std::shared_ptr<Node<Key, T>> root, 
								   std::shared_ptr<Node<Key, T>> beforeMin,
								   std::shared_ptr<Node<Key, T>> afterMax,
								   const std::pair<Key, T>& val) {
	if(root == nullptr || root == beforeMin || root == afterMax) {
		return afterMax;
	}
	if(val.first == root->value.first) {
		return root;
	}
	if(val.first < root->value.first) {
		return FindAux(root->left, beforeMin, afterMax, val);
	}
	return FindAux(root->right, beforeMin, afterMax, val);
}

template <typename Key, typename T>
std::pair<std::shared_ptr<Node<Key, T>>, bool> InsertAux(std::shared_ptr<Node<Key, T>> parent,
									 std::shared_ptr<Node<Key, T>> root, 
								     std::shared_ptr<Node<Key, T>> beforeMin,
								     std::shared_ptr<Node<Key, T>> afterMax,
								     const std::pair<Key, T>& val) {

	if(root == nullptr) {
		root = std::make_shared<Node<Key, T>>(val, 1, parent, nullptr, nullptr);
		return std::make_pair(root, true);
	}
	if(root == beforeMin) {
		root = std::make_shared<Node<Key, T>>(val, 1, parent, beforeMin, nullptr);
		beforeMin->parent = root;
		return std::make_pair(root, true);
	}
	if(root == afterMax) {
		root = std::make_shared<Node<Key, T>>(val, 1, parent, nullptr, afterMax);
		afterMax->parent = root;
		return std::make_pair(root, true);
	}
	if(val.first == root->value.first) {
		return std::make_pair(root, false);
	}
	std::pair<std::shared_ptr<Node<Key, T>>, bool>  insertPair = std::make_pair(nullptr, false);
	if(val.first < root->value.first) {
		insertPair = InsertAux(root, root->left, beforeMin, afterMax, val);
		root->left = insertPair.first;
	}
	if(val.first > root->value.first) {
		insertPair = InsertAux(root, root->right, beforeMin, afterMax, val);
		root->right = insertPair.first;
	}
	root->size = 1 + root->right->size + root->left->size;
	return std::make_pair(root, insertPair.second);
}

} // namespace

template <typename Key, typename T>
class BinarySearchTree {
public:
	using iterator = BinarySearchTreeIt<Key, T>;
	using value_type = std::pair<Key, T>;
	BinarySearchTree();
	iterator Find(const value_type& val); // see how to get const_iterator
	std::pair<iterator, bool> Insert(const value_type& val);
	bool Empty() const;
	iterator Begin() const;
	iterator End() const;

private:
	std::shared_ptr<Node<Key, T>> root = nullptr; // firstInserted
	std::shared_ptr<Node<Key, T>> beforeMin = nullptr;
	std::shared_ptr<Node<Key, T>> afterMax = nullptr;
};


template <typename Key, typename T>
BinarySearchTree<Key, T>::BinarySearchTree()
{
	beforeMin = std::make_shared<Node<Key, T>>(Node<Key, T>(value_type()));
	afterMax = std::make_shared<Node<Key, T>>(Node<Key, T>(value_type()));
}


template <typename Key, typename T>
bool BinarySearchTree<Key, T>::Empty() const {
	return root == nullptr;
}

template<typename Key, typename T>
typename BinarySearchTree<Key, T>::iterator BinarySearchTree<Key, T>::Find(const value_type& val) {
	auto findNode = FindAux(root, beforeMin, afterMax, val);
	return BinarySearchTreeIt<Key, T>(findNode, beforeMin, afterMax);

}

template<typename Key, typename T>
std::pair<typename BinarySearchTree<Key, T>::iterator, bool> BinarySearchTree<Key, T>::Insert(const value_type& val) {
	if(Empty()) {
		root = std::make_shared<Node<Key, T>>(val, 1, nullptr, beforeMin, afterMax);
		beforeMin->parent = root;
		afterMax->parent = root;
		return std::make_pair(Find(val), true);
	}
	auto insertPair = InsertAux(root->parent, root, beforeMin, afterMax, val);
	return std::make_pair(Find(val), insertPair.second);

}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::iterator BinarySearchTree<Key, T>::Begin() const {
	return BinarySearchTreeIt<Key, T>(beforeMin->parent, beforeMin, afterMax);
}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::iterator BinarySearchTree<Key, T>::End() const {
	return BinarySearchTreeIt<Key, T>(afterMax, beforeMin, afterMax);
}

