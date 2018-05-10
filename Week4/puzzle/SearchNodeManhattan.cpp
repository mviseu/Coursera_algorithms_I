#include "SearchNodeManhattan.h"

namespace {

int GetTotalManhattanNumber(const SearchNode& sn) {
	const auto manhattanNode = dynamic_cast<const SearchNodeManhattan&>(sn);
	return sn.GetSizeOfNodeChain() + manhattanNode.GetCurrentPriority();
}

} // namespace

SearchNodeManhattan::SearchNodeManhattan(const SearchNodeData& dt) : data(dt) {
	const auto prevNode = dt.GetPreviousSearchNode();
	if(prevNode != nullptr) {
		const auto prevSearch = dynamic_cast<const SearchNodeManhattan&>(*prevNode);
		currPriority = prevSearch.GetCurrentPriority() + GetManhattanDifference(prevSearch.GetCurrentBoard(),
															  dt.GetCurrentBoard());
	} else {
		currPriority = dt.GetCurrentBoard().Manhattan();
	}
}

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