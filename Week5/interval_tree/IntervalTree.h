#pragma once
#include <algorithm>
#include <memory>
#include <utility>

struct Interval {
	Interval(int low, int high) : lo(low), hi(high) {}
	int lo;
	int hi;
};

bool operator==(const Interval& lhs, const Interval& rhs);
bool operator!=(const Interval& lhs, const Interval& rhs);
bool StartsBefore(const Interval& lhs, const Interval& rhs);
int GetMaxEndPoint(const Interval& lhs, const Interval& rhs);

struct Node {
	Node(const Interval& interv, int maxPoint, std::unique_ptr<Node> lf, std::unique_ptr<Node> ri) : interval(interv), maxEndPoint(maxPoint), left(std::move(lf)), right(std::move(ri)) {}
	Interval interval;
	int maxEndPoint;
	std::unique_ptr<Node> left;
	std::unique_ptr<Node> right;

};

class IntervalTree {
public:
	void Delete(const Interval& interv);
	void Insert(const Interval& interv);
private:
	std::unique_ptr<Node> m_root = nullptr;
};
