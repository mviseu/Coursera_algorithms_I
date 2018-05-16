#pragma once
#include "BinarySearchNode.h"
#include "BinarySearchTreeIt.h"
#include <functional>
#include <memory>

template<typename Key, typename T, typename Compare = std::less<Key>>
class BinarySearchTree {
	using iterator = BinarySearchTreeIt<Key, T>;
public:
	BinarySearchTree() = default;
	iterator Begin() const;
	iterator End() const;
private:
	std::shared_ptr<Node<Key, T>> root; // firstInserted
};

/*
template<typename Key, typename T>
BinarySearchTree<Key, T>::iterator BinarySearchTree<Key, T>::Begin() { const // prob-> not O(constant) with BinarySearchTree
	// find minimum
	// construct iterator with minimum and root
	return BinarySearchTreeIt<Key, T>();
}
*/
