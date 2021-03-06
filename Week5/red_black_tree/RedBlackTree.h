#pragma once
#include "Optional.h"
#include <assert.h>
#include <memory>
#include <utility>

enum struct Colour {red, black};

template <typename Key, typename Value>
struct Node {
	Node(const std::pair<Key, Value>& val, std::unique_ptr<Node> lf, std::unique_ptr<Node> rt, Colour linkParent)
	: keyVal(val), left(std::move(lf)), right(std::move(rt)), colour(linkParent) {}
	std::pair<Key, Value> keyVal;
	std::unique_ptr<Node> left;
	std::unique_ptr<Node> right;
	Colour colour = Colour::black;
};

namespace {

template<typename Key, typename Value>
std::unique_ptr<Node<Key, Value>> LeftRotation(std::unique_ptr<Node<Key, Value>> top) {
	assert(top != nullptr);
	assert(top->right != nullptr);
	assert(top->right->colour == Colour::red);
	auto newTop = std::move(top->right);
	top->right = std::move(newTop->left);
	newTop->left = std::move(top);
	newTop->colour = newTop->left->colour;
	newTop->left->colour = Colour::red;
	return newTop;
}

template<typename Key, typename Value>
std::unique_ptr<Node<Key, Value>> RightRotation(std::unique_ptr<Node<Key, Value>> top) {
	assert(top != nullptr);
	assert(top->left != nullptr);
	assert(top->left->colour == Colour::red);
	auto newTop = std::move(top->left);
	top->left = std::move(newTop->right);
	newTop->right = std::move(top);
	newTop->colour = newTop->right->colour;
	newTop->right->colour = Colour::red;
	return newTop;
}

template<typename Key, typename Value>
std::unique_ptr<Node<Key, Value>> ColourFlip(std::unique_ptr<Node<Key, Value>> top) {
	assert(top != nullptr);
	assert(top->left != nullptr);
	assert(top->right != nullptr);
	assert(top->left->colour == Colour::red);
	assert(top->right->colour == Colour::red);
	assert(top->colour == Colour::black);
	top->right->colour = Colour::black;
	top->left->colour = Colour::black;
	top->colour = Colour::red;
	return top;
}

template<typename Key, typename Value>
bool IsTargetLess(const Node<Key, Value>& node, const Key& key) {
	return key < node.keyVal.first;
}

template<typename Key, typename Value>
bool IsTargetSame(const Node<Key, Value>& node, const Key& key) {
	return node.keyVal.first == key;
}

template<typename Key, typename Value>
bool IsLeftRed(const Node<Key, Value>& node) {
	return node.left != nullptr && node.left->colour == Colour::red;
}

template<typename Key, typename Value>
bool IsRightRed(const Node<Key, Value>& node) {
	return node.right != nullptr && node.right->colour == Colour::red;
}

template<typename Key, typename Value>
std::unique_ptr<Node<Key, Value>> InsertRec(std::unique_ptr<Node<Key, Value>> nodePtr, const std::pair<Key, Value>& val) {
	if(nodePtr == nullptr) {
		return std::make_unique<Node<Key, Value>>(val, nullptr, nullptr, Colour::red);
	}
	if(IsTargetSame(*nodePtr, val.first)) {
		return nodePtr;
	}
	if(IsTargetLess(*nodePtr, val.first)) {
		nodePtr->left = InsertRec(std::move(nodePtr->left), val);
	} else {
		nodePtr->right = InsertRec(std::move(nodePtr->right), val);
	}

	assert(nodePtr != nullptr);
	if(IsRightRed(*nodePtr) && !IsLeftRed(*nodePtr)) {
		nodePtr = LeftRotation(std::move(nodePtr));
	}
	if(IsLeftRed(*nodePtr) && IsLeftRed(*nodePtr->left)) {
		nodePtr = RightRotation(std::move(nodePtr));
	}
	if(IsLeftRed(*nodePtr) && IsRightRed(*nodePtr)) {
		nodePtr = ColourFlip(std::move(nodePtr));
	}
	return nodePtr;
}

template <typename Key, typename Value>
Optional<std::pair<Key, Value>> FindRec(const Node<Key, Value>& node, const Key& key) {
	if(IsTargetSame(node, key)) {
		return node.keyVal;
	}
	if(IsTargetLess(node, key)) {
		if(node.left != nullptr) {
			return FindRec(*node.left, key);
		}
	} else {
		if(node.right != nullptr) {
			return FindRec(*node.right, key);
		}
	}
	return nullopt;
}
template <typename Key, typename Value>
void PrintAllRec(const Node<Key, Value>& node) {
	if(node.left) {
		std::cout << node.left->keyVal.first << std::endl;
		PrintAllRec(*node.left);
	}
	if(node.right) {
		std::cout << node.right->keyVal.first << std::endl;
		PrintAllRec(*node.right);
	}

}

} // namespace

template <typename Key, typename Value>
class RedBlackTree {
public:
	void Insert(const std::pair<Key, Value>& val);
	Optional<std::pair<Key, Value>> Find(const Key& key) const;
	void PrintAll() const;
private:
	std::unique_ptr<Node<Key, Value>> m_root;
};

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::Insert(const std::pair<Key, Value>& val) {
	if(m_root == nullptr) {
		m_root = std::make_unique<Node<Key, Value>>(val, nullptr, nullptr, Colour::black);
	} else {
		m_root = InsertRec(std::move(m_root), val);
		m_root->colour = Colour::black;
	}
}

template <typename Key, typename Value>
Optional<std::pair<Key, Value>> RedBlackTree<Key, Value>::Find(const Key& key) const {
	if(m_root == nullptr) {
		return nullopt;
	}
	return FindRec(*m_root, key);
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::PrintAll() const {
	if(m_root == nullptr) {
		return;
	}
	std::cout << m_root->keyVal.first << std::endl;
	PrintAllRec(*m_root);
}
