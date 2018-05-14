#pragma once
#include "BinarySearchNode.h"
#include <functional>
#include <memory>

template<typename Key, typename T, typename Compare = std::less<Key>>
class BinarySearchTree {
public:
	BinarySearchTree() = default;
private:
	std::shared_ptr<Node<Key, T>> root;
};