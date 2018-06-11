#pragma once
#include <algorithm>
#include <iterator>


constexpr int k = 2;

struct Node {
	Node(int (&pt)[k], Node* lft = nullptr, Node* rt = nullptr)
	: left(lft), right(rt) {
		std::copy(std::begin(pt), std::end(pt), std::begin(pt));
	}
	int point[k] = {0};
	Node* left = nullptr;
	Node* right = nullptr;
};

namespace {

bool IsPointToAddLess(int pointAlreadyTree[], int pointToAdd[], int axisToDivide) {
	return pointToAdd[axisToDivide] < pointAlreadyTree[axisToDivide];
}

bool IsPointToAddGreater(int pointAlreadyTree[], int pointToAdd[], int axisToDivide) {
	return IsPointToAddLess(pointToAdd, pointAlreadyTree, axisToDivide);
}

Node* InsertRec(Node* node, int (&pointToAdd)[k], int depth) { 
	if(node == nullptr) {
		return new Node(pointToAdd);
	}
	const auto axisToDivide = depth % k;
	const auto increasedDepth = depth + 1; 
	if(IsPointToAddLess(node->point, pointToAdd, axisToDivide)) {
		return InsertRec(node->left, pointToAdd, increasedDepth);
	}
	if(IsPointToAddGreater(node->point, pointToAdd, axisToDivide)) {
		return InsertRec(node->right, pointToAdd, increasedDepth);
	}
	return node;
}

} // namespace

struct KdTree {
public:
	KdTree() = default;
	void Insert(int (&point)[k]);

private:
	Node* m_root = nullptr;
};


void KdTree::Insert(int (&point)[k]) {
	m_root = InsertRec(m_root, point, 0);
}