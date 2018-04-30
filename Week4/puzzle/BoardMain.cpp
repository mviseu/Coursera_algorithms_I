#include "Board.h"
#include "CountInversions.h"
#include <iostream>
#include <iterator>

void PrintVector(std::ostream& os, const std::vector<int>& vec) {
	std::ostream_iterator<int> out(os, " ");
	std::copy(vec.begin(), vec.end(), out);
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
	std::cout << bdNIs1.Hamming() << std::endl;
	std::cout << bd.Manhattan() << std::endl;

	std::vector<int> vec1 = {1, 3, 4, 2, 5, 7, 8, 6};
	std::cout << CountInversions(vec1.begin(), vec1.end()) << std::endl;
	PrintVector(std::cout, vec1);

	auto oddNonSolvable = Board(std::vector<std::vector<int>>({{1, 2, 3}, {4, 5, 6}, {8, 7, 0}}));
	auto oddSolvable = Board(std::vector<std::vector<int>>({{0, 1, 3}, {4, 2, 5}, {7, 8, 6}}));
	auto evenSolvable = Board(std::vector<std::vector<int>>({{1, 2, 3, 4}, {5, 0, 6, 8}, {9, 10, 7, 11}, {13, 14, 15, 12}}));
	std::cout << "Is board solvable: " << oddNonSolvable.IsSolvable() << std::endl;
	std::cout << "Is board solvable: " << oddSolvable.IsSolvable() << std::endl;
	std::cout << "Is board solvable: " << evenSolvable.IsSolvable() << std::endl;
	return 0;
}
