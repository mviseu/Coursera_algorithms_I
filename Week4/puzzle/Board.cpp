#include "Board.h"
#include <cmath>
#include <stdexcept>

namespace {

void CheckDimension(int rowOrColumn, int N) {
	if(rowOrColumn < 0 || rowOrColumn >= N) {
		throw std::out_of_range("row or column dimensions must be between 0 and N-1.");
	}
}

} // namespace


Board::Board(const std::vector<std::vector<int>>& board) : m_board(board) {}
Board::Board(std::vector<std::vector<int>>&& board) : m_board(std::move(board)) {}
int Board::TileAt(int row, int col) const {
	const auto N = static_cast<int>(m_board.size());
	CheckDimension(row, N);
	CheckDimension(col, N);
	return m_board[row][col];
}
