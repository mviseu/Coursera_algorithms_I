#pragma once
#include <vector>

class Board {
friend bool operator==(const Board& lhs, const Board& rhs);
friend bool operator!=(const Board& lhs, const Board& rhs);

public:
	Board(const std::vector<std::vector<int>>& board);
	int TileAt(int row, int col) const;
	int Size() const;
	int Hamming() const;
	int Manhattan() const;
	bool IsGoal() const;
	bool IsSolvable() const;
private:
	std::vector<int> m_board;
};
