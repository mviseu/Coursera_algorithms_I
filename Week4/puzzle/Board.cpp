#include "Board.h"
#include <algorithm>
#include <cmath>
#include <iterator>
#include <stdexcept>

namespace {

void CheckDimension(int rowOrColumn, int N) {
	if(rowOrColumn < 0 || rowOrColumn >= N) {
		throw std::out_of_range("row or column dimensions must be between 0 and N-1.");
	}
}

int GetColumnIndex(int arrayIndex, int N) {
	return arrayIndex % N;
}

int GetRowIndex(int arrayIndex, int N) {
	const auto colIndex = GetColumnIndex(arrayIndex, N);
	return (arrayIndex - colIndex) / N;
}

int DiffRow(int indexGoal, int indexActual, int N) {
	return std::abs(GetRowIndex(indexGoal, N) - GetRowIndex(indexActual, N));	
}

int DiffColumn(int indexGoal, int indexActual, int N) {
	return std::abs(GetColumnIndex(indexGoal, N) - GetColumnIndex(indexActual, N));	
}

int GetSingleValueManhattan(int indexGoal, int indexActual, int N) {
	const auto diffRow = DiffRow(indexGoal, indexActual, N);
	const auto diffCol = DiffColumn(indexGoal, indexActual, N);
	return diffRow + diffCol;
}

int GetIndexFromDistance(std::vector<int>::const_iterator beg, std::vector<int>::const_iterator it) {
	return static_cast<int>(std::distance(beg, it));
}

int GetActualIndex(int indexGoal, const std::vector<int>& board) {
	const auto itActual = std::find(board.begin(), board.end(), indexGoal + 1);
	return GetIndexFromDistance(board.begin(), itActual);
}

int GetSingleValueManhattan(std::vector<int>::const_iterator itGoal, const std::vector<int>& board) {
	const auto N = static_cast<int>(std::sqrt(board.size()));
	const auto indexGoal = GetIndexFromDistance(board.begin(), itGoal);
	const auto indexActual = GetActualIndex(indexGoal, board);
	return GetSingleValueManhattan(indexGoal, indexActual, N);
}

} // namespace


Board::Board(const std::vector<std::vector<int>>& board) {
	for(const auto& val : board) {
		m_board.insert(m_board.end(), val.begin(), val.end());
	}
}

int Board::TileAt(int row, int col) const {
	const auto N = static_cast<int>(Size());
	CheckDimension(row, N);
	CheckDimension(col, N);
	return m_board[row * N + col];
}

int Board::Size() const {
	return static_cast<int>(std::sqrt(m_board.size()));
}

int Board::Hamming() const {
	if(Size() == 0) {
		return 0;
	}
	auto pos = 1;
	return static_cast<int>(std::count_if(m_board.begin(), std::prev(m_board.end()), 
						[&pos](int val) {return val != pos++;}));
}

int Board::Manhattan() const {
	if(Size() == 0) {
		return 0;
	}
	auto manhattan = 0;
	for(auto itGoal = m_board.begin(); itGoal != std::prev(m_board.end()); ++itGoal) {
		manhattan += GetSingleValueManhattan(itGoal, m_board);
	}
	return manhattan;
}
