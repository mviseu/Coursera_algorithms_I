#include "Board.h"
#include "CountInversions.h"
#include <algorithm>
#include <cmath>
#include <iterator>
#include <stdexcept>

namespace {

int BoardSize(const std::vector<int>& board) {
	return static_cast<int>(std::sqrt(board.size()));
}

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
	const auto N = BoardSize(board);
	const auto indexGoal = GetIndexFromDistance(board.begin(), itGoal);
	const auto indexActual = GetActualIndex(indexGoal, board);
	return GetSingleValueManhattan(indexGoal, indexActual, N);
}

bool IsNumberOdd(int N) {
	return N % 2 != 0;
}

std::vector<int> GetBoardWithNoBlank(const std::vector<int>& board) {
	auto boardWithNoBlank = std::vector<int>();
	std::copy_if(board.cbegin(), board.cend(), std::back_inserter(boardWithNoBlank), [](int i) {return i !=0;});
	return boardWithNoBlank;
}

int CountBoardInversions(const std::vector<int>& board) {
	auto boardWithNoBlank = GetBoardWithNoBlank(board);
	return CountInversions(boardWithNoBlank.cbegin(), boardWithNoBlank.cend());
}

int AreBoardInversionsOdd(const std::vector<int>& board) {
	return IsNumberOdd(CountBoardInversions(board));
}

bool IsOddBoardSolvable(const std::vector<int>& board) {
	return !AreBoardInversionsOdd(board);
}

int GetBlankRowIndex(const std::vector<int>& board) {
	const auto itBlank = std::find(board.cbegin(), board.cend(), 0);
	return GetRowIndex(GetIndexFromDistance(board.cbegin(), itBlank), BoardSize(board));
}

bool IsEvenBoardSolvable(const std::vector<int>& board) {
	const auto blankRowPlusInversions = GetBlankRowIndex(board) + CountBoardInversions(board);
	return IsNumberOdd(blankRowPlusInversions);
}

} // namespace


Board::Board(const std::vector<std::vector<int>>& board) {
	for(const auto& val : board) {
		m_board.insert(m_board.end(), val.begin(), val.end());
	}
}

int Board::TileAt(int row, int col) const {
	const auto N = Size();
	CheckDimension(row, N);
	CheckDimension(col, N);
	return m_board[row * N + col];
}

int Board::Size() const {
	return BoardSize(m_board);
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

bool Board::IsGoal() const {
	return Hamming() == 0;
}

bool Board::IsSolvable() const {
	if(IsNumberOdd(Size())) {
		return IsOddBoardSolvable(m_board);
	}
	return IsEvenBoardSolvable(m_board);
}

bool operator==(const Board& lhs, const Board& rhs) {
	return lhs.m_board == rhs.m_board;
}

bool operator!=(const Board& lhs, const Board& rhs) {
	return !(lhs == rhs);
}
