#pragma once
#include <utility>
#include <memory>

template <typename Key, typename T>
struct Node {
	Node(const std::pair<Key, T>& val) : value(val) {}
	Node() = default;
	std::pair<Key, T> value;
	int size{1};
	std::shared_ptr<Node> parent;
	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;
};

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


