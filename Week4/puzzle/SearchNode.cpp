#include "SearchNode.h"

namespace {
int GetTotalHammingNumber(const SearchNode& sn) {
	return sn.movesSoFar + sn.currBoard.Hamming();
}
} // namespace

bool GetHammingCompare(const SearchNode& lhs, const SearchNode& rhs) {
	return GetTotalHammingNumber(lhs) > GetTotalHammingNumber(rhs);
}
