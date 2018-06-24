#include "IntervalTree.h"
#include <algorithm>
#include <vector>

bool operator==(const Interval& lhs, const Interval& rhs) {
	return lhs.lo == rhs.lo && lhs.hi == rhs.hi;
}

bool operator!=(const Interval& lhs, const Interval& rhs) {
	return !(lhs == rhs);
}

bool StartsBefore(const Interval& lhs, const Interval& rhs) {
	return lhs.lo < rhs.lo;
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

} // namespace

void IntervalTree::Insert(const Interval& interv) {
	m_root = InsertRec(std::move(m_root), interv);
}

void IntervalTree::Delete(const Interval& interv) {
	m_root = DeleteRec(std::move(m_root), interv);
}