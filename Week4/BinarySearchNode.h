#pragma once
#include <utility>
#include <memory>

template <typename Key, typename T>
struct Node {
	Node(const std::pair<Key, T>& val) : value(val) {}
	Node(const std::pair<Key, T>& val, int sz, std::shared_ptr<Node<Key, T>> prt, std::shared_ptr<Node<Key, T>> lt, std::shared_ptr<Node<Key, T>> rt)
	: value(val), size(sz), parent(prt), left(lt), right(rt) {}
	Node() = default;
	std::pair<const Key, T> value;
	int size{0};
	std::shared_ptr<Node<Key, T>> parent = nullptr;
	std::shared_ptr<Node<Key, T>> left = nullptr;
	std::shared_ptr<Node<Key, T>> right = nullptr;
};


template <typename Key, typename T>
bool IsNodeKeyLessThanTarget(const Node<Key, T>& node, const Key& targetKey) {
	return node.value.first < targetKey;
}

template <typename Key, typename T>
bool IsNodeKeyGreaterThanTarget(const Node<Key, T>& node, const Key& targetKey) {
	return node.value.first > targetKey;
}

template <typename Key, typename T>
bool IsNodeKeyEqualToTarget(const Node<Key, T>& node, const Key& targetKey) {
	return !IsNodeKeyLessThanTarget(node, targetKey) && !IsNodeKeyGreaterThanTarget(node, targetKey);
}

template <typename Key, typename T>
bool IsParentLeftOfNode(const Node<Key, T>& node) {
	if(!node.parent) {
		return false;
	}
	return node.parent->value.first < node.value.first;
}

template <typename Key, typename T>
bool IsParentRightOfNode(const Node<Key, T>& node) {
	if(!node.parent) {
		return false;
	}
	return node.value.first < node.parent->value.first;
}

template <typename Key, typename T>
bool DoesParentExist(const Node<Key, T>& node) {
	return node.parent != nullptr;
}

template <typename Key, typename T>
bool IsLeftNull(const Node<Key, T>& node) {
	return node.left == nullptr;
}

template <typename Key, typename T>
bool IsRightNull(const Node<Key, T>& node) {
	return node.right == nullptr;
}

template <typename Key, typename T>
bool IsParentNull(const Node<Key, T>& node) {
	return node.parent == nullptr;
}

template<typename Key, typename T>
std::shared_ptr<Node<Key, T>> CreateANewNode(const std::pair<const Key, T>& val, std::shared_ptr<Node<Key, T>> par) {
	return std::make_shared<Node<Key, T>>(val, 1, par, nullptr, nullptr);
}

template<typename Key, typename T>
std::shared_ptr<Node<Key, T>> CreateANewMin(const std::pair<const Key, T>& val, std::shared_ptr<Node<Key, T>> par, std::shared_ptr<Node<Key, T>> beforeMin) {
	return std::make_shared<Node<Key, T>>(val, 1, par, beforeMin, nullptr);
}

template<typename Key, typename T>
std::shared_ptr<Node<Key, T>> CreateANewMax(const std::pair<const Key, T>& val, std::shared_ptr<Node<Key, T>> par, std::shared_ptr<Node<Key, T>> afterMax) {
	return std::make_shared<Node<Key, T>>(val, 1, par, nullptr, afterMax);
}

template<typename Key, typename T>
std::shared_ptr<Node<Key, T>> CreateANewTree(const std::pair<const Key, T>& val, std::shared_ptr<Node<Key, T>> beforeMin, std::shared_ptr<Node<Key, T>> afterMax) {
	return std::make_shared<Node<Key, T>>(val, 1, nullptr, beforeMin, afterMax);
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
void PointNodeRelativesToItself(std::shared_ptr<Node<Key, T>> node) {
	MakeChildrenPointToNode(node);
	if(IsParentLeftOfNode(*node)) {
		MakeLeftParentPointToNode(node);
	}
	if(IsParentRightOfNode(*node)) {
		MakeRightParentPointToNode(node);
	}	
}

template <typename Key, typename T> 
int GetSizeOfLeftSubTree(const Node<Key, T>& node) {
	if(!IsLeftNull(node)) {
		return node.left->size;
	}
	return 0;
}

