#include "SearchNodeManhattan.h"

namespace {

int GetTotalManhattanNumber(const SearchNode& sn) {
	return sn.GetSizeOfNodeChain() + sn.GetCurrentBoard().Manhattan();
}

} // namespace

bool SearchNodeManhattan::GetPriorityCompare(const SearchNode& rhs) const {
	return GetTotalManhattanNumber(*this) > GetTotalManhattanNumber(rhs);
}

bool SearchNodeManhattan::HasGoalBeenReached() const {
	return data.HasGoalBeenReached();
}

std::vector<Board> SearchNodeManhattan::GetAllNeighbors() const {
	return data.GetAllNeighbors();
}

bool SearchNodeManhattan::IsThereAPreviousNode() const {
	return data.IsThereAPreviousNode();
}

bool SearchNodeManhattan::IsThisThePreviousBoard(const Board& board) const {
	return data.IsThisThePreviousBoard(board);
}

int SearchNodeManhattan::IncrementNrMoves() const {
	return data.IncrementNrMoves();
}

std::vector<Board> SearchNodeManhattan::GetSequenceOfBoards() const {
	return data.GetSequenceOfBoards();
}

int SearchNodeManhattan::GetSizeOfNodeChain() const {
	return data.GetSizeOfNodeChain();
}

std::shared_ptr<SearchNode> SearchNodeManhattan::GetPreviousSearchNode() const {
	return data.GetPreviousSearchNode();
}

Board SearchNodeManhattan::GetCurrentBoard() const {
	return data.GetCurrentBoard();
}