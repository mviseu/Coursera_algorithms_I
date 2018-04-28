#pragma once
#include <vector>

class Board {
public:
	Board(const std::vector<std::vector<int>>& board);
	Board(std::vector<std::vector<int>>&& board);
	int TileAt(int row, int col) const;
private:
	std::vector<std::vector<int>> m_board;
};
