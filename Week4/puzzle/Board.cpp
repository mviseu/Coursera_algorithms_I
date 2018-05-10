#include "Board.h"
#include "CountInversions.h"
#include <algorithm>
#include <cmath>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <iomanip>

namespace {
enum struct Direction {up, down, left, right};

int GetColumnIndex(int arrayIndex, int N) {
	return arrayIndex % N;
}

int GetRowIndex(int arrayIndex, int N) {
	return arrayIndex / N;
}

int GetIndex(int row, int col, int N) {
	return N * row + col;
}

std::pair<int, int> GetRowColumn(int arrayIndex, int N) {
	return std::make_pair(GetRowIndex(arrayIndex, N),
						  GetColumnIndex(arrayIndex, N));
}

int BoardSize(const std::vector<int>& board) {
	return static_cast<int>(std::sqrt(board.size()));
}

void CheckDimension(int rowOrColumn, int N) {
	if(rowOrColumn < 0 || rowOrColumn >= N) {
		throw std::out_of_range("row or column dimensions must be between 0 and N-1.");
	}
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

int GetBlankArrayIndex(const std::vector<int>& board) {
	const auto itBlank = std::find(board.cbegin(), board.cend(), 0);
	return GetIndexFromDistance(board.cbegin(), itBlank);
}

int GetBlankRowIndex(const std::vector<int>& board) {
	return GetRowIndex(GetBlankArrayIndex(board), BoardSize(board));
}

bool IsEvenBoardSolvable(const std::vector<int>& board) {
	const auto blankRowPlusInversions = GetBlankRowIndex(board) + CountBoardInversions(board);
	return IsNumberOdd(blankRowPlusInversions);
}

bool IsBlankInTopRow(int indexBlank, int N) {
	return GetRowIndex(indexBlank, N) == 0;
}

bool IsBlankInBottomRow(int indexBlank, int N) {
	return GetRowIndex(indexBlank, N) == N - 1;
}

bool IsBlankInLeftMostColumn(int indexBlank, int N) {
	return GetColumnIndex(indexBlank, N) == 0;
}

bool IsBlankInRightMostColumn(int indexBlank, int N) {
	return GetColumnIndex(indexBlank, N) == N - 1;
}

int GetIndexToShiftedPosition(int currIndex, Direction dir, int N) {
	const auto currRow = GetRowColumn(currIndex, N).first;
	const auto currCol = GetRowColumn(currIndex, N).second;
	switch(dir) {
	case Direction::up:
		return GetIndex(currRow - 1, currCol, N);
	case Direction::down:
		return GetIndex(currRow + 1, currCol, N);
	case Direction::left:
		return GetIndex(currRow, currCol - 1, N);
	case Direction::right:
		return GetIndex(currRow, currCol + 1, N);
	default:
		return GetIndex(currRow, currCol, N);
	}
}

Board GetBoard(const std::vector<int>& boardVec) {
	std::vector<std::vector<int>> boardRet;
	const auto N = BoardSize(boardVec);
	auto it = boardVec.begin();
	while(it != boardVec.end()) {
		boardRet.push_back(std::vector<int>(it, it + N));
		std::advance(it, N);
	}
	return Board(boardRet);
}

Board GetBoardWithBlankShifted(int indexBlank, Direction dir, const std::vector<int>& board) {
	auto newBoard = board;
	auto beg = newBoard.begin();
	auto oldBlankIt = beg + indexBlank;
	auto newBlankIt = beg + GetIndexToShiftedPosition(indexBlank, dir, BoardSize(board));
	std::iter_swap(oldBlankIt, newBlankIt);
	return GetBoard(newBoard);
}

Board GetBoardWithBlankShiftedToLeft(int indexBlank, const std::vector<int>& board) {
	return GetBoardWithBlankShifted(indexBlank, Direction::left, board);
}

Board GetBoardWithBlankShiftedToRight(int indexBlank, const std::vector<int>& board) {
	return GetBoardWithBlankShifted(indexBlank, Direction::right, board);
}

Board GetBoardWithBlankShiftedUp(int indexBlank, const std::vector<int>& board) {
	return GetBoardWithBlankShifted(indexBlank, Direction::up, board);
}

Board GetBoardWithBlankShiftedDown(int indexBlank, const std::vector<int>& board) {
	return GetBoardWithBlankShifted(indexBlank, Direction::down, board);
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

std::vector<Board> Board::Neighbors() const {
	std::vector<Board> neighbors;
	const auto blankIndex = GetBlankArrayIndex(m_board);
	const auto N = Size();
	if(!IsBlankInLeftMostColumn(blankIndex, N)) {
		neighbors.push_back(GetBoardWithBlankShiftedToLeft(blankIndex, m_board));
	}
	if(!IsBlankInRightMostColumn(blankIndex, N)) {
		neighbors.push_back(GetBoardWithBlankShiftedToRight(blankIndex, m_board));
	}
	if(!IsBlankInTopRow(blankIndex, N)) {
		neighbors.push_back(GetBoardWithBlankShiftedUp(blankIndex, m_board));
	}
	if(!IsBlankInBottomRow(blankIndex, N)) {
		neighbors.push_back(GetBoardWithBlankShiftedDown(blankIndex, m_board));
	}
	return neighbors;
}

bool operator==(const Board& lhs, const Board& rhs) {
	return lhs.m_board == rhs.m_board;
}

bool operator!=(const Board& lhs, const Board& rhs) {
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
	const auto N = board.Size();
	for(auto it = board.m_board.begin(); it != board.m_board.end(); std::advance(it, N)) {
		os << std::endl;
		for(auto itInThrees = it; itInThrees != it + N; ++itInThrees) {
			os << std::internal;
			os << std::setw(12);
			os << *itInThrees;
		}
	}
	os << std::right;
	return os;
}

std::istream& operator>>(std::istream& is, Board& board) {
	int N{0};
	if(is >> N) {
		board.m_board = std::vector<int>();
		std::istream_iterator<int> in(is);
		std::generate_n(std::back_inserter(board.m_board), N * N, [&in]() {
			return *in++;}
		);
	}
	return is;
}

int GetManhattanDifference(const Board& prevBoard, const Board& currBoard) {
	const auto it = std::find(prevBoard.m_board.cbegin(), prevBoard.m_board.cend(), 0);
	const auto index = GetIndexFromDistance(prevBoard.m_board.cbegin(), it);
	const auto changedElement = *(currBoard.m_board.cbegin() + index);
	const auto goalIndex = changedElement - 1;
	const auto prevManhattan = GetSingleValueManhattan(prevBoard.m_board.cbegin() + goalIndex, prevBoard.m_board);
	const auto currManhattan = GetSingleValueManhattan(currBoard.m_board.cbegin() + goalIndex, currBoard.m_board);
	return currManhattan - prevManhattan;
}