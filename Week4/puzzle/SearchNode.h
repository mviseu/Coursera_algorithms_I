#pragma once
#include "Board.h"
#include <memory>

struct SearchNode {
	SearchNode(const Board& curr, std::shared_ptr<SearchNode> prev, int nrMoves) : currBoard(curr), prevNode(prev), movesSoFar(nrMoves) {}
	SearchNode() = default;
	Board currBoard;
	std::shared_ptr<SearchNode> prevNode;
	int movesSoFar {0};
};

bool GetHammingCompare(const SearchNode& lhs, const SearchNode& rhs);