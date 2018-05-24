#pragma once
#include "BinarySearchNode.h"
#include <memory>
#include <utility>

template<typename Key, typename T>
struct Nodes {
	Nodes() {
		beforeMin = std::make_shared<Node<Key, T>>(Node<Key, T>(std::make_pair(Key(), T())));
		afterMax = std::make_shared<Node<Key, T>>(Node<Key, T>(std::make_pair(Key(), T())));
	}
	Nodes(std::shared_ptr<Node<Key, T>> rt, std::shared_ptr<Node<Key, T>> bfr, std::shared_ptr<Node<Key, T>> afr)
	: root(rt), beforeMin(bfr), afterMax(afr) {}
	std::shared_ptr<Node<Key, T>> root = nullptr;
	std::shared_ptr<Node<Key, T>> beforeMin = nullptr;
	std::shared_ptr<Node<Key, T>> afterMax = nullptr;
};

template<typename Key, typename T>
Nodes<Key, T> GetLeftNodes(const Nodes<Key, T>& nodes) {
	return Nodes<Key, T>(nodes.root->left, nodes.beforeMin, nodes.afterMax);
}

template<typename Key, typename T>
Nodes<Key, T> GetRightNodes(const Nodes<Key, T>& nodes) {
	return Nodes<Key, T>(nodes.root->right, nodes.beforeMin, nodes.afterMax);
}

template<typename Key, typename T>
bool IsRootTheBeforeMin(const Nodes<Key, T>& nodes) {
	return nodes.root == nodes.beforeMin;
}

template<typename Key, typename T>
bool IsRootTheAfterMax(const Nodes<Key, T>& nodes) {
	return nodes.root == nodes.afterMax;
}

template<typename Key, typename T>
bool DoesRootHaveKey(const Nodes<Key, T>& nodes) {
	return !(nodes.root == nullptr || IsRootTheBeforeMin(nodes) || IsRootTheAfterMax(nodes));
}

template<typename Key, typename T>
void LinkBeforeMinParentToRoot(const Nodes<Key, T>& nodes) {
	nodes.beforeMin->parent = nodes.root;
}


template<typename Key, typename T>
void LinkAfterMaxParentToRoot(const Nodes<Key, T>& nodes) {
	nodes.afterMax->parent = nodes.root;
}