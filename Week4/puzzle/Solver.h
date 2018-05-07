#pragma once
#include "Priority.h"
#include "Board.h"
#include "SearchNode.h"
#include <vector>

class Solver {
public:
	Solver(const Board& firstBoard, Priority priority = Priority::hamming);
	int Moves() const;
	std::vector<Board> Solution() const;
private:
	std::shared_ptr<SearchNode> goalBoard;
};