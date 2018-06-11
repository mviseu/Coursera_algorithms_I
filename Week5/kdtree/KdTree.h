#pragma once
#include <algorithm>
#include <iterator>
#include <iostream>

constexpr int k = 2;

struct Node {
	Node(int (&pt)[k], Node* lft = nullptr, Node* rt = nullptr)
	: left(lft), right(rt) {
		std::copy(std::begin(pt), std::end(pt), std::begin(point));
	}
	int point[k] = {0};
	Node* left = nullptr;
	Node* right = nullptr;
};

namespace {

bool IsTargetPointLess(int pointAlreadyTree[], int targetPoint[], int axisToDivide) {
	return targetPoint[axisToDivide] < pointAlreadyTree[axisToDivide];
}

bool IsTargetPointGreater(int pointAlreadyTree[], int targetPoint[], int axisToDivide) {
	return IsTargetPointLess(targetPoint, pointAlreadyTree, axisToDivide);
}

int GetAxisToDivide(int depth) {
	return depth % k;
}

Node* InsertRec(Node* node, int (&pointToAdd)[k], int depth) { 
	if(node == nullptr) {
		return new Node(pointToAdd);
	}
	const auto axisToDivide = GetAxisToDivide(depth);
	const auto increasedDepth = depth + 1; 
	if(IsTargetPointLess(node->point, pointToAdd, axisToDivide)) {
		node->left = InsertRec(node->left, pointToAdd, increasedDepth);
	}
	if(IsTargetPointGreater(node->point, pointToAdd, axisToDivide)) {
		node->right = InsertRec(node->right, pointToAdd, increasedDepth);
	}
	return node;
}

bool AreTwoPointsEqual(int (&point1)[k], int (&point2)[k]) {
	return std::equal(std::begin(point1), std::end(point1), std::begin(point2));
}

bool SearchRec(Node* node, int (&pointToSearch)[k], int depth) {
	if(node == nullptr) {
		return false;
	}
	if(AreTwoPointsEqual(node->point, pointToSearch)) {
		return true;
	}
	const auto axis = GetAxisToDivide(depth);
	const auto increasedDepth = depth + 1;
	if(IsTargetPointLess(node->point, pointToSearch, axis)) {
		return SearchRec(node->left, pointToSearch, increasedDepth);
	}
	return SearchRec(node->right, pointToSearch, increasedDepth);
}

} // namespace

struct KdTree {
public:
	KdTree() = default;
	void Insert(int (&point)[k]);
	bool Search(int (&point)[k]) const;

private:
	Node* m_root = nullptr;
};


void KdTree::Insert(int (&point)[k]) {
	m_root = InsertRec(m_root, point, 0);
}

bool KdTree::Search(int (&point)[k]) const {
	return SearchRec(m_root, point, 0);
}