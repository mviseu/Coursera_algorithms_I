#pragma once
#include "Board.h"
#include "SearchNode.h"
#include <vector>

class Solver {
public:
	Solver(const Board& firstBoard);
	Solver(Board&& firstBoard);
	int Moves() const;
	std::vector<Board> Solution() const;
private:
	SearchNode goalBoard;
};