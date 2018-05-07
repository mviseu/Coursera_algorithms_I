#pragma once
#include "SearchNode.h"
#include "SearchNodeData.h"
#include "Board.h"
#include <memory>

struct SearchNodeHamming : public SearchNode {
public:
	SearchNodeHamming(const SearchNodeData& dt) : data(dt) {}
	SearchNodeHamming() = default;
	bool HasGoalBeenReached() const override;
	std::vector<Board> GetAllNeighbors() const override;
	bool IsThereAPreviousNode() const override;
	bool IsThisThePreviousBoard(const Board& board) const override;
	int IncrementNrMoves() const override;
	std::vector<Board> GetSequenceOfBoards() const override;
	int GetSizeOfNodeChain() const override;
	std::shared_ptr<SearchNode> GetPreviousSearchNode() const override;
	Board GetCurrentBoard() const override;
	SearchNodeData GetSearchNodeData() const {return data;};

private:
	bool GetPriorityCompare(const SearchNode& rhs) const override;
	SearchNodeData data;
};