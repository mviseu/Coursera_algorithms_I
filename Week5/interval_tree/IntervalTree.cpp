#include "IntervalTree.h"
#include <algorithm>
#include <iterator>

bool operator==(const Interval& lhs, const Interval& rhs) {
	return lhs.lo == rhs.lo && lhs.hi == rhs.hi;
}

bool operator!=(const Interval& lhs, const Interval& rhs) {
	return !(lhs == rhs);
}

bool StartsBefore(const Interval& lhs, const Interval& rhs) {
	return lhs.lo < rhs.lo;
}

std::ostream& operator<<(std::ostream& os, const Interval& interv) {
	os << "(" << interv.lo << ", " << interv.hi << ")";
	return os;
}

namespace {
std::unique_ptr<Node> DeleteRec(std::unique_ptr<Node> root, const Interval& interv);

int GetMaxEndPoint(const std::initializer_list<Interval>& intervalList) {
	auto highs = std::vector<int>();
	std::transform(intervalList.begin(), intervalList.end(), std::inserter(highs, highs.end()), [](const Interval& interv) {
		return interv.hi;
	});
	return *std::max_element(highs.cbegin(), highs.cend());
}

bool NodeHasNoChildren(const Node& node) {
	return node.left == nullptr && node.right == nullptr;
}

bool NodeHasOnlyLeftChild(const Node& node) {
	return node.left != nullptr && node.right == nullptr;
}

bool NodeHasOnlyRightChild(const Node& node) {
	return node.right != nullptr && node.left == nullptr;
}

int GetMaxEndPoint(const Node& node) {
	if(NodeHasNoChildren(node)) {
		return node.maxEndPoint;
	} else {
		if(NodeHasOnlyLeftChild(node)) {
			return GetMaxEndPoint({node.interval, node.left->interval});
		} else {
			if(NodeHasOnlyRightChild(node)) {
				return GetMaxEndPoint({node.interval, node.right->interval});
			} else {
				return GetMaxEndPoint({node.interval, node.left->interval, node.right->interval});			}
		}
	}
}

std::unique_ptr<Node> InsertRec(std::unique_ptr<Node> root, const Interval& interv) {
	if(root == nullptr) {
		return std::make_unique<Node>(interv, interv.hi, nullptr, nullptr);
	}
	if(root->interval == interv) {
		return root;
	}
	if(StartsBefore(interv, root->interval)) {
		root->left = InsertRec(std::move(root->left), interv);
	} else {
		root->right = InsertRec(std::move(root->right), interv);
	}
	root->maxEndPoint = GetMaxEndPoint(*root);
	return root;
}

Interval FindMinRec(const Node& node, const Interval& minSoFar) {
	if(node.left != nullptr) {
		return FindMinRec(*node.left, node.left->interval);
	} else {
		return minSoFar;
	}
}

std::unique_ptr<Node> DeleteCurr(std::unique_ptr<Node> root) {
	if(NodeHasNoChildren(*root)) {
		return nullptr;
	} else {
		if(root->right != nullptr) {
			root->interval = FindMinRec(*root->right, root->right->interval);
			root->right = DeleteRec(std::move(root->right), root->interval);
		} else {
			root->interval = FindMinRec(*root->left, root->left->interval);
			root->right = DeleteRec(std::move(root->left), root->interval);
			root->left = nullptr;
		}
		return root;
	}
}

std::unique_ptr<Node> DeleteRec(std::unique_ptr<Node> root, const Interval& interv) {
	if(root == nullptr) {
		return root;
	}
	if(root->interval == interv) {
		root = DeleteCurr(std::move(root));
	} else {
		if(StartsBefore(interv, root->interval)) {
			root->left = DeleteRec(std::move(root->left), interv);
		} else {
			root->right = DeleteRec(std::move(root->right), interv);
		}
	}
	if(root != nullptr) {
		root->maxEndPoint = GetMaxEndPoint(*root);
	}
	return root;
}

bool FindRec(const Node& node, const Interval& interv) {
	if(node.interval == interv) {
		return true;
	}
	if(NodeHasNoChildren(node)) {
		return false;
	}
	if(node.left && StartsBefore(interv, node.interval)) {
		return FindRec(*node.left, interv);
	}
	if(node.right && !StartsBefore(interv, node.interval)) {
		return FindRec(*node.right, interv);
	}
	return false;
}

bool DoAllLeftIntervalsEndBeforeLo(const Node& node, int lo) {
	return node.maxEndPoint < lo;
}

bool DoAllRightIntervalsStartAfterHi(const Node& node, int hi) {
	return node.interval.lo > hi;
}

bool IsValueInRange(int val, const Interval& interv) {
	return val >= interv.lo && val <= interv.hi;
}

bool IsIntervalInRange(const Node& node, const Interval& interv) {
	return IsValueInRange(node.interval.lo, interv) || IsValueInRange(node.interval.hi, interv);
}

void AllOverlappingIntervalsRec(const Node& node, const Interval& interv, std::vector<Interval>& overlaps) {
	if(node.left != nullptr && !DoAllLeftIntervalsEndBeforeLo(*node.left, interv.lo)) {
		AllOverlappingIntervalsRec(*node.left, interv, overlaps);
	}
	if(IsIntervalInRange(node, interv)) {
		overlaps.push_back(node.interval);
	}
	if(node.right != nullptr && !DoAllRightIntervalsStartAfterHi(node, interv.hi)) {
		AllOverlappingIntervalsRec(*node.right, interv, overlaps);
	}
}

} // namespace

void IntervalTree::Insert(const Interval& interv) {
	m_root = InsertRec(std::move(m_root), interv);
}

void IntervalTree::Delete(const Interval& interv) {
	m_root = DeleteRec(std::move(m_root), interv);
}

bool IntervalTree::Find(const Interval& interv) const {
	if(m_root == nullptr) {
		return false;
	}
	return FindRec(*m_root, interv);
}

std::vector<Interval> IntervalTree::AllOverlappingIntervals(const Interval& interv) const {
	std::vector<Interval> overlaps;
	if(m_root == nullptr) {
		return overlaps;
	}
	AllOverlappingIntervalsRec(*m_root, interv, overlaps);
	return overlaps;
}
