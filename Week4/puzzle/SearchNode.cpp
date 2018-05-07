#include "SearchNode.h"

bool GetPriorityCompare(const SearchNode& lhs, const SearchNode& rhs) {
	return typeid(lhs) == typeid(rhs) && lhs.GetPriorityCompare(rhs);
}