#pragma once
#include "SearchNode.h"
#include <memory>

struct SearchNodeData {
public:
	SearchNodeData(const Board& curr, std::shared_ptr<SearchNode> prev, int nrMoves) : currBoard(curr), prevNode(prev), movesSoFar(nrMoves) {}
	SearchNodeData() = default;
	bool HasGoalBeenReached() const;
	std::vector<Board> GetAllNeighbors() const;
	bool IsThereAPreviousNode() const;
	bool IsThisThePreviousBoard(const Board& board) const;
	int IncrementNrMoves() const;
	std::vector<Board> GetSequenceOfBoards() const;
	int GetSizeOfNodeChain() const;
	std::shared_ptr<SearchNode> GetPreviousSearchNode() const;
	Board GetCurrentBoard() const;

private:
	Board currBoard;
	std::shared_ptr<SearchNode> prevNode;
	int movesSoFar {0};
};