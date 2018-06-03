#pragma once
#include "BinarySearchNode.h"
#include <memory>
#include <utility>
#include <iostream>

template<typename Key, typename T>
struct Nodes {
	Nodes() {
		beforeMin = std::make_shared<Node<Key, T>>(std::make_pair(Key(), T()));
		afterMax = std::make_shared<Node<Key, T>>(std::make_pair(Key(), T()));
		beforeMin->right = afterMax;
		afterMax->left = beforeMin;
	}
	Nodes(std::shared_ptr<Node<Key, T>> rt, std::shared_ptr<Node<Key, T>> bfr, std::shared_ptr<Node<Key, T>> afr)
	: node(rt), beforeMin(bfr), afterMax(afr) {}
	std::shared_ptr<Node<Key, T>> node = nullptr; // change name to node
	std::shared_ptr<Node<Key, T>> beforeMin = nullptr;
	std::shared_ptr<Node<Key, T>> afterMax = nullptr;
};

template<typename Key, typename T>
Nodes<Key, T> GetLeftNodes(const Nodes<Key, T>& nodes) {
	// nodes must not have null node
	return Nodes<Key, T>(nodes.node->left, nodes.beforeMin, nodes.afterMax);
}

template<typename Key, typename T>
Nodes<Key, T> GetRightNodes(const Nodes<Key, T>& nodes) {
	// nodes must not have null node
	return Nodes<Key, T>(nodes.node->right, nodes.beforeMin, nodes.afterMax);
}

template<typename Key, typename T>
Nodes<Key, T> GetAfterMaxNodes(const Nodes<Key, T>& nodes) {
	// nodes must not have null node
	return Nodes<Key, T>(nodes.afterMax, nodes.beforeMin, nodes.afterMax);
}

template<typename Key, typename T>
Nodes<Key, T> GetBeforeMinNodes(const Nodes<Key, T>& nodes) {
	// nodes must not have null node
	return Nodes<Key, T>(nodes.beforeMin, nodes.beforeMin, nodes.afterMax);
}

template<typename Key, typename T>
Nodes<Key, T> GetParentNodes(const Nodes<Key, T>& nodes) {
	// nodes must not have null node
	return Nodes<Key, T>(nodes.node->parent, nodes.beforeMin, nodes.afterMax);
}

template<typename Key, typename T>
bool IsRootTheBeforeMin(const Nodes<Key, T>& nodes) {
	return nodes.node == nodes.beforeMin;
}

template<typename Key, typename T>
bool IsRootTheAfterMax(const Nodes<Key, T>& nodes) {
	return nodes.node == nodes.afterMax;
}

template<typename Key, typename T>
bool IsLeftTheBeforeMin(const Nodes<Key, T>& nodes) {
	return !IsRootNull(nodes) && nodes.node->left == nodes.beforeMin;
}

template<typename Key, typename T>
bool IsRootNull(const Nodes<Key, T>& nodes) {
	return nodes.node == nullptr;	
}

template<typename Key, typename T>
bool DoesRootHaveKey(const Nodes<Key, T>& nodes) {
	return !(nodes.node == nullptr || IsRootTheBeforeMin(nodes) || IsRootTheAfterMax(nodes));
}

template<typename Key, typename T>
void LinkBeforeMinParentToRoot(const Nodes<Key, T>& nodes) {
	nodes.beforeMin->parent = nodes.node;
}

template<typename Key, typename T>
void LinkAfterMaxParentToRoot(const Nodes<Key, T>& nodes) {
	nodes.afterMax->parent = nodes.node;
}

template <typename Key, typename T>
bool IsRightGreater(const Nodes<Key, T>& nodes) {
	// node has populated node -> find greater to right of it, if exists!
	auto right = GetRightNodes(nodes);
	return !IsRootNull(right) && !IsRootTheAfterMax(right);
}

template <typename Key, typename T>
bool IsLeftLess(const Nodes<Key, T>& nodes) {
	// node has populated node -> find greater to right of it, if exists!
	auto left = GetLeftNodes(nodes);
	return !IsRootNull(left) && !IsRootTheBeforeMin(left);
}

template <typename Key, typename T>
Nodes<Key, T> MaxOfCurrentTree(const Nodes<Key, T>& nodes) {
	auto max = nodes;
	while(IsRightGreater(max)) {
		max = GetRightNodes(max);
	}
	return max;
}

template <typename Key, typename T>
Nodes<Key, T> MinOfCurrentTree(const Nodes<Key, T>& nodes)  {
	auto min = nodes;
	while(IsLeftLess(min)) {
		min = GetLeftNodes(min);
	}
	return min;
}

template <typename Key, typename T>
Nodes<Key, T> Min(const Nodes<Key, T>& nodes)  {
	return Nodes<Key, T>(nodes.beforeMin->parent, nodes.beforeMin, nodes.afterMax);
}

template<typename Key, typename T>
bool AreNonKeyValuesTheSame(const Nodes<Key, T>& lhs, const Nodes<Key, T>& rhs) {
	return lhs.beforeMin == rhs.beforeMin && lhs.afterMax == rhs.afterMax;
}

template<typename Key, typename T>
bool IsTreeAtTheRoot(const Nodes<Key, T>& nodes) {
	return !IsRootNull(nodes) && nodes.node->parent == nullptr;
}

template<typename Key, typename T>
bool IsRootTheOnlyExistingNode(const Nodes<Key, T>& nodes) {
	if(DoesRootHaveKey(nodes)) {
		return nodes.node->left == nodes.beforeMin && nodes.node->right == nodes.afterMax;
	}	
	return false;
}

template<typename Key, typename T>
int GetSizeBasedOnChildren(const Nodes<Key, T>& nodes) {
	auto sz = 0;
	if(DoesRootHaveKey(nodes)) {
		sz += 1;
	}
	if(IsLeftLess(nodes)) {
		sz += nodes.node->left->size;
	}
	if(IsRightGreater(nodes)){
		sz += nodes.node->right->size;
	}
	return sz;
}

template<typename Key, typename T>
Nodes<Key, T> UpdateRightNodes(const Nodes<Key, T>& currNodes, const Nodes<Key, T>& rightNodes) {
	auto nodeWithNewRight = std::make_shared<Node<Key, T>>(currNodes.node->value, currNodes.node->size, currNodes.node->parent, currNodes.node->left, rightNodes.node);
	auto updatedNodes = Nodes<Key, T>(nodeWithNewRight, currNodes.beforeMin, rightNodes.afterMax);
	updatedNodes.node->size = GetSizeBasedOnChildren(updatedNodes);
	PointNodeRelativesToItself(updatedNodes.node);
	return updatedNodes;
}

template<typename Key, typename T>
Nodes<Key, T> UpdateLeftNodes(const Nodes<Key, T>& currNodes, const Nodes<Key, T>& leftNodes) {
	auto nodeWithNewLeft = std::make_shared<Node<Key, T>>(currNodes.node->value, currNodes.node->size, currNodes.node->parent, leftNodes.node, currNodes.node->right);
	auto updatedNodes = Nodes<Key, T>(nodeWithNewLeft, leftNodes.beforeMin, currNodes.afterMax);
	updatedNodes.node->size = GetSizeBasedOnChildren(updatedNodes);
	PointNodeRelativesToItself(updatedNodes.node);
	return updatedNodes;
}