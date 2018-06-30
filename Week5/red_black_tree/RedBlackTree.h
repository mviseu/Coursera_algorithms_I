#pragma once
#include <assert.h>
#include <memory>
#include <utility>

enum struct Colour {red, black};

template <typename Key, typename Value>
struct Node {
	Node(const std::pair<Key, Value>& val, std::unique_ptr<Node> lf, std::unique_ptr<Node> rt, Colour linkParent)
	: keyVal(val), left(std::move(lf)), right(std::move(right)), colour(linkParent) {}
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
	newTop->colour = top->colour;
	top->colour = Colour::red;
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
	newTop->colour = top->colour;
	top->colour = Colour::red;
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
bool IsKeyLess(const Node<Key, Value>& node, const std::pair<Key, Value>& val) {
	return node.keyVal.first < val.first;
}

template<typename Key, typename Value>
bool IsKeySame(const Node<Key, Value>& node, const std::pair<Key, Value>& val) {
	return node.keyVal.first == val.first;
}

template<typename Key, typename Value>
bool AreChildrenPopulated(const Node<Key, Value>& node) {
	return node.left != nullptr;
}

template<typename Key, typename Value>
std::unique_ptr<Node<Key, Value>> InsertRec(std::unique_ptr<Node<Key, Value>> nodePtr, const std::pair<Key, Value>& val) {
	assert(nodePtr != nullptr);
	if(IsKeySame(*nodePtr, val)) {
		return nodePtr;
	} else {
		if(AreBlacChildrenPopulated(*nodePtr)) {
			return InsertBelow(std::move(nodePtr), val);

		} else {
			return InsertCurrent(std::move(nodePtr), val);
		}
	}
}

} // namespace

template <typename Key, typename Value>
class RedBlackTree {
public:
	void Insert(const std::pair<Key, Value>& val);
private:
	Node<Key, Value> m_root;
};

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::Insert(const std::pair<Key, Value>& val) {
	if(m_root == nullptr) {
		m_root = std::make_unique(Node(val, nullptr, nullptr, Colour::black));
	} else {
		m_root = InsertRec(std::move(m_root), val);
	}
}
