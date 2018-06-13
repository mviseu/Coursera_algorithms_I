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
	} else {
		node->right = InsertRec(node->right, pointToAdd, increasedDepth);
	}
	return node;
}

bool AreTwoPointsEqual(int (&point1)[k], int (&point2)[k]) {
	return std::equal(std::begin(point1), std::end(point1), std::begin(point2));
}

bool IsRightChildPopulated(const Node& node) {
	return node.right != nullptr;
}


bool IsLeftChildPopulated(const Node& node) {
	return node.left != nullptr;
}

bool IsAxisSameAsAxisOfMin(int depth, int depthMinDimension) {
	return GetAxisToDivide(depth) == GetAxisToDivide(depthMinDimension);
}

*Node FindMinWhenAxisCurrSameAsAxisMin(Node* node, int depth, int depthMinDimension) {
	if(IsLeftChildPopulated(*node)) {
		return FindMin(node->left, depth + 1, depthMinDimension);
	} else {
		return node;
	}	
}

*Node FindMin(Node* node, int depth, int depthMinDimension) {
	assert(node != nullptr);
	if(IsAxisSameAsAxisOfMin(depth, depthMinDimension)) {
		return FindMinWhenAxisCurrSameAsAxisMin(node, depth, depthMinDimension);
	} else {
		// if left null, look to right
		// if right null, look to left
		// if both null, return current
		// if both populated choose min of current, right, left
	}
}


*Node DeleteCurrentNode(Node* node, int depth) {
	if(IsRightChildPopulated(*node)) {
		// delete when right child populated only or both populated
		// find the successor point (min on right)
		// delete successor on right
		// replace node to be deleted with successor

		
	} else {
		if(IsLeftChildPopulated(*node)) {
			// delete when left child populated only
			// find successor which is the min on the left side
			// delete successor on left
			// replace node to be deleted with sucessor
			// append remaining lhs tree on right of the successor
		} else {
			// delete when no child populated
			delete node;
			return nullptr;
		}
	}
}

Node* DeleteRec(Node* node, int (&pointToDel)[k], int depth) {
	if(node == nullptr) {
		return node;
	}
	if(AreTwoPointsEqual(node->point, pointToDel)) {
		return DeleteCurrentNode(node, depth);
	}
	const auto axis = GetAxisToDivide(depth);
	const auto increasedDepth = depth + 1;
	if(IsTargetPointLess(node->point, pointToDel, axis)) {
		node->left = DeleteRec(node->left, pointToDel, increasedDepth);
	} else {
		node->right = DeleteRec(node->right, pointToDel, increasedDepth);
	}
	return node;
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
	void Delete(int (&point)[k]);
	bool Search(int (&point)[k]) const;

private:
	Node* m_root = nullptr;
};


void KdTree::Insert(int (&point)[k]) {
	m_root = InsertRec(m_root, point, 0);
}

void KdTree::Delete(int (&point)[k]) {
	m_root = DeleteRec(m_root, point, 0);
}

bool KdTree::Search(int (&point)[k]) const {
	return SearchRec(m_root, point, 0);
}