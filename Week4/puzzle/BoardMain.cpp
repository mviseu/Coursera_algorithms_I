#include "Board.h"
#include <iostream>

int main() {
	const auto vec = std::vector<std::vector<int>>({
													{8, 1, 3},
													{4, 0, 2},
													{7, 6, 5}
														});
	const auto bdNIs1 = Board(std::vector<std::vector<int>>({{1}}));
	const auto bd = Board(vec);
	std::cout << bd.Hamming() << std::endl;
	std::cout << bdNIs1.Hamming() << std::endl;
	std::cout << bd.Manhattan() << std::endl;
	return 0;
}
