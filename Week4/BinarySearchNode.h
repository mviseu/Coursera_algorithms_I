#pragma once
#include <utility>
#include <memory>

template <typename Key, typename T>
struct Node {
	Node(const std::pair<Key, T>& val) : value(val) {}
	Node() = default;
	std::pair<Key, T> value;
	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;
};
