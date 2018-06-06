#pragma once
#include "BinarySearchNode.h"
#include "BinarySearchNodes.h"
#include "BinarySearchTreeIt.h"
#include "Range.h"
#include <functional>
#include <memory>
#include <utility>
#include <iostream>
#include <iterator>
#include <optional>

namespace {

template <typename Key, typename T>
std::shared_ptr<Node<Key, T>> FindAux(const Nodes<Key, T>& nodes,
								   	  const Key& key) {
	if(!DoesRootHaveKey(nodes)) {
		return nodes.afterMax;
	}
	if(IsNodeKeyEqualToTarget(*nodes.node, key)) {
		return nodes.node;
	}
	if(IsNodeKeyGreaterThanTarget(*nodes.node, key)) {
		return FindAux(GetLeftNodes(nodes), key);
	}
	return FindAux(GetRightNodes(nodes), key);
}

template <typename Key, typename T>
std::optional<std::pair<std::shared_ptr<Node<Key, T>>, bool>>
InsertIfFinalNode(std::shared_ptr<Node<Key, T>> parent, const Nodes<Key, T>& nodes, const std::pair<const Key, T>& val) {
	if(nodes.node == nullptr) {
		return std::make_pair(CreateANewNode(val, parent), true);
	}
	if(IsRootTheBeforeMin(nodes)) {
		auto newNodes = nodes;
		newNodes.node = CreateANewMin(val, parent, newNodes.beforeMin);
		LinkBeforeMinParentToRoot(newNodes);
		return std::make_pair(newNodes.node, true);
	}
	if(IsRootTheAfterMax(nodes)) {
		auto newNodes = nodes;
		newNodes.node = CreateANewMax(val, parent, newNodes.afterMax);
		LinkAfterMaxParentToRoot(newNodes);
		return std::make_pair(newNodes.node, true);
	}
	if(IsNodeKeyEqualToTarget(*nodes.node, val.first)) {
		return std::make_pair(nodes.node, false);
	}
	return std::nullopt;
}


template <typename Key, typename T>
std::pair<std::shared_ptr<Node<Key, T>>, bool> InsertAux(std::shared_ptr<Node<Key, T>> parent,
									 					 const Nodes<Key, T>& nodes,
								     					 const std::pair<const Key, T>& val) {
	if(const auto newInsert = InsertIfFinalNode(parent, nodes, val)) {
		return *newInsert;
	}
	std::pair<std::shared_ptr<Node<Key, T>>, bool> InsertPair = std::make_pair(nullptr, false);
	if(IsNodeKeyGreaterThanTarget(*nodes.node, val.first)) {
		InsertPair = InsertAux(nodes.node, GetLeftNodes(nodes), val);
		nodes.node->left = InsertPair.first;
	}
	if(IsNodeKeyLessThanTarget(*nodes.node, val.first)) {
		InsertPair = InsertAux(nodes.node, GetRightNodes(nodes), val);
		nodes.node->right = InsertPair.first;
	}
	nodes.node->size = GetSizeBasedOnChildren(nodes);
	return std::make_pair(nodes.node, InsertPair.second);

}

template <typename Key, typename T>
Nodes<Key, T> EraseWhenRightChildNull(const Nodes<Key, T>& nodes) {
	if(!IsLeftNull(*nodes.node)) {
		nodes.node->left->parent = nodes.node->parent;
	}
	if(IsParentLeftOfNode(*nodes.node)) {
		nodes.node->parent->right = nodes.node->left;
	}
	if(IsParentRightOfNode(*nodes.node)) {
		nodes.node->parent->left = nodes.node->left;
	}
	return GetLeftNodes(nodes);
}

template <typename Key, typename T>
Nodes<Key, T> EraseWhenLeftChildNull(const Nodes<Key, T>& nodes) {
	if(!IsRightNull(*nodes.node)) {
		nodes.node->right->parent = nodes.node->parent;
	}
	if(IsParentLeftOfNode(*nodes.node)) {
		nodes.node->parent->right = nodes.node->right;
	}
	if(IsParentRightOfNode(*nodes.node)) {
		nodes.node->parent->left = nodes.node->right;
	}
	return GetRightNodes(nodes);
}

template <typename Key, typename T>
Nodes<Key, T> EraseAux(const Nodes<Key, T>& nodes, const Key& key);

template <typename Key, typename T>
Nodes<Key, T> ReplaceEraseByMinOnRight(const Nodes<Key, T>& nodes) {
	auto minVal = (MinOfCurrentTree(GetRightNodes(nodes)).node)->value;
	auto successorPair = std::pair<const Key, T>(minVal.first, minVal.second);
	auto treeNoSuccessor = EraseAux(nodes, successorPair.first); 
	auto newNode = std::make_shared<Node<Key, T>>(successorPair, treeNoSuccessor.node->size, treeNoSuccessor.node->parent, treeNoSuccessor.node->left, treeNoSuccessor.node->right);
	PointNodeRelativesToItself(newNode);
	return Nodes<Key, T>(newNode, nodes.beforeMin, nodes.afterMax);
}

template <typename Key, typename T>
Nodes<Key, T> ReplaceEraseByMaxOnLeft(const Nodes<Key, T>& nodes) {
	auto maxVal = (MaxOfCurrentTree(GetLeftNodes(nodes)).node)->value;
	auto successorPair = std::pair<const Key, T>(maxVal);
	auto treeNoSuccessor = EraseAux(nodes, successorPair.first);
	auto newNode = std::make_shared<Node<Key, T>>(successorPair, treeNoSuccessor.node->size, treeNoSuccessor.node->parent, treeNoSuccessor.node->left, treeNoSuccessor.node->right);
	PointNodeRelativesToItself(newNode);
	return Nodes<Key, T>(newNode, treeNoSuccessor.beforeMin, treeNoSuccessor.afterMax);
}

template <typename Key, typename T>
Nodes<Key, T> EraseRoot(const Nodes<Key, T>& nodes) {
	if(IsRootTheOnlyExistingNode(nodes)) {
		nodes.afterMax->parent = nullptr;
		nodes.beforeMin->parent = nullptr;
		nodes.afterMax->left = nodes.beforeMin;
		nodes.beforeMin->right = nodes.afterMax;
		return Nodes<Key, T>(nullptr, nodes.afterMax, nodes.beforeMin);
	}
	if(IsLeftTheBeforeMin(nodes)) {
		return ReplaceEraseByMinOnRight(nodes);
	}
	return ReplaceEraseByMaxOnLeft(nodes);
}

template <typename Key, typename T>
Nodes<Key, T> EraseWhenOneChildIsNull(const Nodes<Key, T>& nodes) {
		// check the size
	if(IsRightNull(*nodes.node)) {
		return EraseWhenRightChildNull(nodes);
	}
	return EraseWhenLeftChildNull(nodes);
}

template <typename Key, typename T>
Nodes<Key, T> EraseCurrentNode(const Nodes<Key, T>& nodes) {
	if(IsTreeAtTheRoot(nodes)) {
		return EraseRoot(nodes);
	}
	if(IsRightNull(*nodes.node) || IsLeftNull(*nodes.node)) {
		return EraseWhenOneChildIsNull(nodes);
	}
	if(IsRightGreater(nodes)) {
		return ReplaceEraseByMinOnRight(nodes);
	}
	if(IsLeftLess(nodes)) {
		return ReplaceEraseByMaxOnLeft(nodes);
	}
	return nodes;	
}

template <typename Key, typename T>
Nodes<Key, T> EraseAux(const Nodes<Key, T>& nodes, const Key& key) {
	// missing: update the size
	assert(DoesRootHaveKey(nodes));
	if(IsNodeKeyEqualToTarget(*nodes.node, key)) {
		return EraseCurrentNode(nodes);
	}
	auto nodesNew = nodes;
	if(IsNodeKeyLessThanTarget(*nodes.node, key)) {
		auto rightNodes = EraseAux(GetRightNodes(nodes), key);
		return UpdateRightNodes(nodes, rightNodes);
	}
	auto leftNodes = EraseAux(GetLeftNodes(nodes), key);
	return UpdateLeftNodes(nodes, leftNodes);
}

template <typename Key, typename T>
int RankAux(const Nodes<Key, T>& nodes, const Key& targetKey) {
	if(!DoesRootHaveKey(nodes)) {
		return 0;
	}
	if(IsNodeKeyEqualToTarget(*nodes.node, targetKey)) {
		return GetSizeOfLeftSubTree(*nodes.node);
	}
	if(IsNodeKeyLessThanTarget(*nodes.node, targetKey)) {
		return 1 + GetSizeOfLeftSubTree(*nodes.node) + RankAux(GetRightNodes(nodes), targetKey); 
	}
	return RankAux(GetLeftNodes(nodes), targetKey);
}


template <typename Key, typename T>
std::vector<Key> RangeSearchAux(const Nodes<Key, T>& nodes, const Range<Key>& rg, const std::vector<Key>& inRange) {
	auto ret = inRange;
	if(DoesRootHaveKey(nodes)) {
		const auto key = nodes.node->value.first;
		if(IsKeyGreaterLow(key, rg)) {
			ret = RangeSearchAux(GetLeftNodes(nodes), rg, ret);
		}
		if(IsKeyInRange(key, rg)) {
			ret.push_back(key);	
		}
		if(IsKeyLessHigh(key, rg)) {
			ret = RangeSearchAux(GetRightNodes(nodes), rg, ret);
		}
	}
	return ret;
}

} // namespace

template <typename Key, typename T>
class BinarySearchTree {
public:
	using iterator = BinarySearchTreeIt<Key, T>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using value_type = std::pair<const  Key, T>;
	BinarySearchTree() = default;
	BinarySearchTree(const BinarySearchTree&) = delete;
	BinarySearchTree(BinarySearchTree&&) = delete;
	BinarySearchTree&operator=(const BinarySearchTree&) = delete;
	BinarySearchTree&operator=(BinarySearchTree&&) = delete;
	iterator Find(const Key& key) const; // see how to get const_iterator
	std::pair<iterator, bool> Insert(const value_type& val);
	iterator Erase(iterator pos);
	bool Empty() const;
	bool Contains(const Key& key) const;
	int Rank(const Key& targetKey) const;
	int RangeCount(const Range<Key>& rg) const;
	std::vector<Key> RangeSearch(const Range<Key>& rg) const;
	iterator Begin() const;
	iterator End() const;
	reverse_iterator RBegin() const;
	reverse_iterator REnd() const;

private:
	Nodes<Key, T> m_nodesAtRoot;
};

template <typename Key, typename T>
bool BinarySearchTree<Key, T>::Empty() const {
	return m_nodesAtRoot.node == nullptr;
}

template<typename Key, typename T>
typename BinarySearchTree<Key, T>::iterator BinarySearchTree<Key, T>::Find(const Key& key) const {
	auto FindNode = FindAux(m_nodesAtRoot, key);
	return iterator(Nodes<Key, T>(FindNode, m_nodesAtRoot.beforeMin, m_nodesAtRoot.afterMax));

}

template<typename Key, typename T>
std::pair<typename BinarySearchTree<Key, T>::iterator, bool> BinarySearchTree<Key, T>::Insert(const value_type& val) {
	if(Empty()) {
		m_nodesAtRoot.node = CreateANewTree(val, m_nodesAtRoot.beforeMin, m_nodesAtRoot.afterMax);
		m_nodesAtRoot.beforeMin->parent = m_nodesAtRoot.node;
		m_nodesAtRoot.afterMax->parent = m_nodesAtRoot.node;
		return std::make_pair(Find(val.first), true);
	}
	auto InsertPair = InsertAux(m_nodesAtRoot.node->parent, m_nodesAtRoot, val);
	return std::make_pair(Find(val.first), InsertPair.second);

}

template<typename Key, typename T>
typename BinarySearchTree<Key, T>::iterator BinarySearchTree<Key, T>::Erase(iterator pos) {
	if(pos == End()) {
		return End();
	}
	auto key = pos->first;
	auto FindNode = FindAux(m_nodesAtRoot, key);
	std::optional<Key> nextKey;
	auto itNext = ++iterator(Nodes<Key, T>(FindNode, m_nodesAtRoot.beforeMin, m_nodesAtRoot.afterMax));
	if(itNext != End()) {
		nextKey = itNext->first;
	}
	m_nodesAtRoot = EraseAux(m_nodesAtRoot, key);
	auto Findnext = Find(*nextKey);
	return nextKey ? Findnext : End();
}

//Rank -> how many keys < target key?
template<typename Key, typename T>
int BinarySearchTree<Key, T>::Rank(const Key& targetKey) const {
	return RankAux(m_nodesAtRoot, targetKey);
}

template<typename Key, typename T>
bool BinarySearchTree<Key, T>::Contains(const Key& key) const {
	return Find(key) != End();
}

//Range Count -> how many keys between loKey and highKey?
template<typename Key, typename T>
int BinarySearchTree<Key, T>::RangeCount(const Range<Key>& rg) const {
	int rangeCount = Rank(rg.hi) - Rank(rg.lo);
	if(Contains(rg.hi)) {
		++rangeCount;
	}
	return rangeCount;
}

template<typename Key, typename T>
std::vector<Key> BinarySearchTree<Key, T>::RangeSearch(const Range<Key>& rg) const {
	return RangeSearchAux(m_nodesAtRoot, rg, std::vector<Key>());
}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::iterator BinarySearchTree<Key, T>::Begin() const {
	if(Empty()) {
		return End();
	}
	return iterator(Min(m_nodesAtRoot));
}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::iterator BinarySearchTree<Key, T>::End() const {
	return iterator(GetAfterMaxNodes(m_nodesAtRoot));
}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::reverse_iterator BinarySearchTree<Key, T>::RBegin() const {
	return std::reverse_iterator<iterator>(End());
}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::reverse_iterator BinarySearchTree<Key, T>::REnd() const {
	return std::reverse_iterator<iterator>(Begin());
}