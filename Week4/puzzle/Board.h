#pragma once
#include <vector>

class Board {
public:
	Board(const std::vector<std::vector<int>>& board);
	int TileAt(int row, int col) const;
	int Size() const;
	int Hamming() const;
	int Manhattan() const;
private:
	std::vector<int> m_board;
};
