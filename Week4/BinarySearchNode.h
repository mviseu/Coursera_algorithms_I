#pragma once
#include <utility>
#include <memory>

template <typename Key, typename T>
struct Node {
	Node(const std::pair<Key, T>& val) : value(val) {}
	Node(const std::pair<Key, T>& val, int sz, std::shared_ptr<Node> prt, std::shared_ptr<Node> lt, std::shared_ptr<Node> rt)
	: value(val), size(sz), parent(prt), left(lt), right(rt) {}
	Node() = default;
	std::pair<Key, T> value;
	int size{0};
	std::shared_ptr<Node> parent = nullptr;
	std::shared_ptr<Node> left = nullptr;
	std::shared_ptr<Node> right = nullptr;
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

template <typename Key, typename T>
int GetSizeBasedOnChildren(const Node<Key, T>& node) {
	auto sz = 1;
	if(node.left != nullptr) {
		sz += node.left->size;
	}
	if(node.right != nullptr) {
		sz += node.right->size;
	}
	return sz;

}


