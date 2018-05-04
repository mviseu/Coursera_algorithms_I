#pragma once
#include <iostream>
#include <vector>

class Board;
bool operator==(const Board& lhs, const Board& rhs);
bool operator!=(const Board& lhs, const Board& rhs);
std::ostream& operator<<(std::ostream& os, const Board& board);
std::istream& operator>>(std::istream& is, Board& board);

class Board {
friend bool operator==(const Board& lhs, const Board& rhs);
friend bool operator!=(const Board& lhs, const Board& rhs);
friend std::ostream& operator<<(std::ostream&, const Board&);
friend std::istream& operator>>(std::istream& is, Board& board);

public:
	Board(const std::vector<std::vector<int>>& board = {{}});
	int TileAt(int row, int col) const;
	int Size() const;
	int Hamming() const;
	int Manhattan() const;
	bool IsGoal() const;
	bool IsSolvable() const;
	std::vector<Board> Neighbors() const;
private:
	std::vector<int> m_board;
};
