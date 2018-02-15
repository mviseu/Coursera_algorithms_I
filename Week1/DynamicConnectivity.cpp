#include "QuickFind.h"
#include <iostream>

int main() {
	std::cout << "Specify number of elements in the grid:" << std::endl;
	int nr_elements(0);
	if (std::cin >> nr_elements) {
		alg::QuickFind grid(nr_elements);
		std::cout << "Specify connected pairs of integers: " << std::endl;
		int i(0),j(0);
		while(std::cin >> i && std::cin >> j) {
			if(grid.Connected(i, j)) {
				std::cout << "These 2 are already connected! Try again..." << std::endl;
			} else {
				grid.Union(i,j);
				std::cout << "Connected element " << i << " and " << j << std::endl;
			}
		}
	}
	return 0;
}