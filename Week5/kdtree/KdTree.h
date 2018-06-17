#pragma once
#include <algorithm>
#include <cassert>
#include <iterator>
#include <iostream>
#include <optional>
#include <utility>
#include <vector>

constexpr int k = 2;

namespace {

void CopyToPoint(int* point, const int* base) {
	for(auto i = 0; i < k; ++i) {
		point[i] = base[i];
	}
}

int* CreatePoint(const int* base) {
	int* newPoint = new int[k]();
	CopyToPoint(newPoint, base);
	return newPoint;
}

} // namespace

struct Node {
	Node(int (&pt)[k], Node* lft = nullptr, Node* rt = nullptr)
	: point(CreatePoint(pt)), left(lft), right(rt) {}
	~Node() {
		delete [] point;
	}
	int* point = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
};

namespace {

Node* FindMinRec(Node* node, int depth, int depthMinDimension);
Node* DeleteRec(Node* node, int pointToDel[k], int depth);

bool IsFirstLess(const int first[], const int second[], int axisToDivide) {
	return first[axisToDivide] < second[axisToDivide];
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
	if(IsFirstLess(pointToAdd, node->point, axisToDivide)) {
		node->left = InsertRec(node->left, pointToAdd, increasedDepth);
	} else {
		node->right = InsertRec(node->right, pointToAdd, increasedDepth);
	}
	return node;
}

bool AreTwoPointsEqual(const int point1[k], const int point2[k]) {
	auto equal = true;
	for(auto i = 0; i < k; ++i) {
		if(point1[i] != point2[i]) {
			equal = false;
			break;
		}
	}
	return equal;
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

Node* GetMinNode(Node* first, Node* second, int axisDivide) {
	assert(first != nullptr);
	assert(second != nullptr);
	if(IsFirstLess(first->point, second->point, axisDivide)) {
		return first;
	}
	return second;
}

Node* FindMinWhenAxisCurrSameAsAxisMin(Node* node, int depth, int depthMinDimension) {
	if(IsLeftChildPopulated(*node)) {
		return FindMinRec(node->left, depth + 1, depthMinDimension);
	} else {
		return node;
	}
}

Node* FindMinWhenAxisCurrDiffAxisMin(Node* node, int depth, int depthMinDimension) {
	auto min = node;
	const auto depthIncreased = depth + 1;
	if(IsLeftChildPopulated(*node)) {
		const auto minLeft = FindMinRec(node->left, depthIncreased, depthMinDimension);
		min = GetMinNode(min, minLeft, depthMinDimension); 
	}
	if(IsRightChildPopulated(*node)) {
		const auto minRight = FindMinRec(node->right, depthIncreased, depthMinDimension);
		min = GetMinNode(min, minRight, depthMinDimension);
	}
	return min;
}

Node* FindMinRec(Node* node, int depth, int depthMinDimension) {
	assert(node != nullptr);
	if(IsAxisSameAsAxisOfMin(depth, depthMinDimension)) {
		return FindMinWhenAxisCurrSameAsAxisMin(node, depth, depthMinDimension);
	} else {
		return FindMinWhenAxisCurrDiffAxisMin(node, depth, depthMinDimension);
	}
}

void ReplacePointWithSuccessor(Node& node, const Node& min) {
	CopyToPoint(node.point, min.point);
}

Node* ReplaceWithSuccessorByRightDelete(Node* node, int depth) {
	auto min = FindMinRec(node->right, depth + 1, depth);
	ReplacePointWithSuccessor(*node, *min);
	node->right = DeleteRec(node->right, min->point, depth + 1);
	return node;
}


Node* ReplaceWithSuccessorByLeftDelete(Node* node, int depth) {
	assert(node->right == nullptr);
	auto min = FindMinRec(node->left, depth + 1, depth);
	ReplacePointWithSuccessor(*node, *min);
	node->right = DeleteRec(node->left, min->point, depth + 1);
	node->left = nullptr;
	return node;
}

Node* DeleteCurrentNode(Node* node, int depth) {
	if(IsRightChildPopulated(*node)) {
		return ReplaceWithSuccessorByRightDelete(node, depth);
	} else {
		if(IsLeftChildPopulated(*node)) {
			return ReplaceWithSuccessorByLeftDelete(node, depth);
		} else {
			delete node;
			return nullptr;
		}
	}
}

Node* DeleteRec(Node* node, int pointToDel[k], int depth) {
	if(node == nullptr) {
		return node;
	}
	if(AreTwoPointsEqual(node->point, pointToDel)) {
		return DeleteCurrentNode(node, depth);
	}
	const auto axis = GetAxisToDivide(depth);
	const auto increasedDepth = depth + 1;
	if(IsFirstLess(pointToDel, node->point, axis)) {
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
	if(IsFirstLess(pointToSearch, node->point, axis)) {
		return SearchRec(node->left, pointToSearch, increasedDepth);
	}
	return SearchRec(node->right, pointToSearch, increasedDepth);
}

/*
bool IsNodeInRange(const Node& node, const std::pair<int [k], int[k]>& bounds, int axisDiv) {
	return !IsFirstLess(node.point, bounds.first, axisDiv) && !IsFirstLess(bounds.second, node.point, axisDiv);
}
*/
/*
void SearchRangeRec(std::vector<int [k]>& inBounds, Node* node, const std::pair<int [k], int[k]>& bounds, int depth) {
	if(node == nullptr) {
		return;
	}
	const auto axisDiv = GetAxisToDivide(depth);
	if(IsNodeInRange(*node, bounds, axisDiv)) {
		int newPoint[k] = {0};
		std::copy(std::begin(node->point), std::end(node->point), std::begin(newPoint));
		inBounds.push_back(newPoint);
	}
	const auto depthIncrease = depth + 1;
	if(IsFirstLess(node->point, bounds.first, axisDiv)) {
		SearchRangeRec(inBounds, node->right, bounds, depthIncrease);
	}
	if(IsFirstLess(bounds.second, node->point, axisDiv)) {
		SearchRangeRec(inBounds, node->left, bounds, depthIncrease);
	}
}
*/

} // namespace

struct KdTree {
public:
	KdTree() = default;
	void Insert(int (&point)[k]);
	void Delete(int (&point)[k]);
	std::optional<int*> FindMin() const;
	bool Search(int (&point)[k]) const;
	//std::vector<int [k]> SearchRange(const std::pair<int [k], int[k]>&) const;

private:
	Node* m_root = nullptr;
};


void KdTree::Insert(int (&point)[k]) {
	m_root = InsertRec(m_root, point, 0);
}


void KdTree::Delete(int (&point)[k]) {
	m_root = DeleteRec(m_root, point, 0);
}


std::optional<int*> KdTree::FindMin() const {
	if(m_root == nullptr) {
		return std::nullopt;
	}
	return FindMinRec(m_root, 0, 0)->point;
}

bool KdTree::Search(int (&point)[k]) const {
	return SearchRec(m_root, point, 0);
}
/*
std::vector<int [k]> KdTree::SearchRange(const std::pair<int [k], int[k]>& bounds) const {
	std::vector<int [k]> inBounds;
	SearchRangeRec(inBounds, m_root, bounds, 0);
	return inBounds;

*/