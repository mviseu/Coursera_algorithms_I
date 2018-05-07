#include "SearchNodeHamming.h"

namespace {

int GetTotalHammingNumber(const SearchNode& sn) {
	return sn.GetSizeOfNodeChain() + sn.GetCurrentBoard().Hamming();
}

} // namespace

bool SearchNodeHamming::GetPriorityCompare(const SearchNode& rhs) const {
	return GetTotalHammingNumber(*this) > GetTotalHammingNumber(rhs);
}

bool SearchNodeHamming::HasGoalBeenReached() const {
	return data.HasGoalBeenReached();
}

std::vector<Board> SearchNodeHamming::GetAllNeighbors() const {
	return data.GetAllNeighbors();
}

bool SearchNodeHamming::IsThereAPreviousNode() const {
	return data.IsThereAPreviousNode();
}

bool SearchNodeHamming::IsThisThePreviousBoard(const Board& board) const {
	return data.IsThisThePreviousBoard(board);
}

int SearchNodeHamming::IncrementNrMoves() const {
	return data.IncrementNrMoves();
}

std::vector<Board> SearchNodeHamming::GetSequenceOfBoards() const {
	return data.GetSequenceOfBoards();
}

int SearchNodeHamming::GetSizeOfNodeChain() const {
	return data.GetSizeOfNodeChain();
}

std::shared_ptr<SearchNode> SearchNodeHamming::GetPreviousSearchNode() const {
	return data.GetPreviousSearchNode();
}

Board SearchNodeHamming::GetCurrentBoard() const {
	return data.GetCurrentBoard();
}