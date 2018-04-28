#include "Board.h"
#include <iostream>

int main() {
	const auto vec = std::vector<std::vector<int>>({
													{0, 1, 3},
													{4, 2, 5},
													{7, 8, 6}
														});
	const auto bd = Board(vec);
	std::cout << bd.TileAt(0, 0) << std::endl;
	std::cout << bd.TileAt(1, 1) << std::endl;
	std::cout << bd.TileAt(2, 1) << std::endl;
	return 0;
}
