#include "SearchNodeData.h"
#include <algorithm>

bool SearchNodeData::HasGoalBeenReached() const {
	return currBoard.IsGoal();
}

std::vector<Board> SearchNodeData::GetAllNeighbors() const {
	return currBoard.Neighbors();
}

bool SearchNodeData::IsThereAPreviousNode() const {
	return prevNode != nullptr;
}

bool SearchNodeData::IsThisThePreviousBoard(const Board& board) const {
	return board == GetPreviousSearchNode()->GetCurrentBoard();
}

int SearchNodeData::IncrementNrMoves() const {
	return movesSoFar + 1;
}

std::vector<Board> SearchNodeData::GetSequenceOfBoards() const {
	std::vector<Board> searchPath;
	searchPath.push_back(currBoard);
	auto node = prevNode;
	while(node) {
		searchPath.push_back(node->GetCurrentBoard());
		node = node->GetPreviousSearchNode();
	}
	std::reverse(searchPath.begin(), searchPath.end());
	return searchPath;
}

int SearchNodeData::GetSizeOfNodeChain() const {
	return movesSoFar;
}

std::shared_ptr<SearchNode> SearchNodeData::GetPreviousSearchNode() const {
	return prevNode;
}

Board SearchNodeData::GetCurrentBoard() const {
	return currBoard;
}