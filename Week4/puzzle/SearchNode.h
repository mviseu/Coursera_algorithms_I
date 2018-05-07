#pragma once
#include "Board.h"
#include <memory>
#include <vector>

struct SearchNode {
friend bool GetPriorityCompare(const SearchNode& lhs, const SearchNode& rhs);
public:
	virtual bool HasGoalBeenReached() const = 0;
	virtual std::vector<Board> GetAllNeighbors() const = 0;
	virtual bool IsThereAPreviousNode() const = 0;
	virtual bool IsThisThePreviousBoard(const Board& board) const = 0;
	virtual int IncrementNrMoves() const = 0;
	virtual std::vector<Board> GetSequenceOfBoards() const = 0;
	virtual int GetSizeOfNodeChain() const = 0;
	virtual std::shared_ptr<SearchNode> GetPreviousSearchNode() const = 0;
	virtual Board GetCurrentBoard() const = 0;
	virtual ~SearchNode() = default;
private:
	virtual bool GetPriorityCompare(const SearchNode& rhs) const = 0;
};

bool GetPriorityCompare(const SearchNode& lhs, const SearchNode& rhs);