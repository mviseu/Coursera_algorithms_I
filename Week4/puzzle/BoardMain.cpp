#include "Board.h"
#include "CountInversions.h"
#include <iostream>
#include <iterator>

void PrintVector(std::ostream& os, const std::vector<int>& vec) {
	std::ostream_iterator<int> out(os, " ");
	std::copy(vec.begin(), vec.end(), out);
}

void PrintNeighbors(std::ostream& os, const Board& board) {
	const auto neighbors = board.Neighbors();
	for(const auto& neighbor : neighbors) {
		os << neighbor << std::endl;
	}	
}

int main() {
	const auto vec = std::vector<std::vector<int>>({
													{8, 1, 3},
													{4, 0, 2},
													{7, 6, 5}
														});
	const auto vecGoal = std::vector<std::vector<int>>({{1, 2, 3}, {4, 5, 6}, {7, 8, 0}});
	const auto bdGoal = Board(vecGoal);
	const auto bdNIs1 = Board(std::vector<std::vector<int>>({{1}}));
	const auto bd = Board(vec);
	std::cout << bd.Hamming() << std::endl;
	std::cout << bd.Manhattan() << std::endl;

	std::vector<int> vec1 = {1, 3, 4, 2, 5, 7, 8, 6};
	std::cout << CountInversions(vec1.begin(), vec1.end()) << std::endl;
	PrintVector(std::cout, vec1);

	auto oddNonSolvable = Board(std::vector<std::vector<int>>({{1, 2, 3}, {4, 5, 6}, {8, 7, 0}}));
	auto oddSolvable = Board(std::vector<std::vector<int>>({{0, 1, 3}, {4, 2, 5}, {7, 8, 6}}));
	auto evenSolvable = Board(std::vector<std::vector<int>>({{1, 2, 3, 4}, {5, 0, 6, 8}, {9, 10, 7, 11}, {13, 14, 15, 12}}));

	const auto boardBlankCanMoveAllDir = Board(std::vector<std::vector<int>>({{1, 2, 3},
																	   {4, 0, 6},
																	   {8, 5, 7}}));
	std::cout << std::endl;
	PrintNeighbors(std::cout, boardBlankCanMoveAllDir);

	const auto blankCannotMoveLeft = Board(std::vector<std::vector<int>>({{1, 2, 3},
																	   {0, 4, 6},
																	   {8, 5, 7}}));
	std::cout << std::endl;
	PrintNeighbors(std::cout, blankCannotMoveLeft);

	const auto blankCannotMoveRight = Board(std::vector<std::vector<int>>({{1, 2, 3},
																	   {4, 6, 0},
																	   {8, 5, 7}}));
	std::cout << std::endl;
	PrintNeighbors(std::cout, blankCannotMoveRight);

	const auto blankCannotMoveUp = Board(std::vector<std::vector<int>>({{1, 0, 3},
																	   {4, 6, 2},
																	   {8, 5, 7}}));
	std::cout << std::endl;
	PrintNeighbors(std::cout, blankCannotMoveUp);

	const auto blankCannotMoveDown = Board(std::vector<std::vector<int>>({{1, 5, 3},
																	   {4, 6, 2},
																	   {8, 0, 7}}));
	std::cout << std::endl;
	std::cout << "Blank cannot move down" << std::endl;
	PrintNeighbors(std::cout, blankCannotMoveDown);	
	return 0;
}
