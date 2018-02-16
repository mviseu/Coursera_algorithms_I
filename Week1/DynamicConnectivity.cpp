#include "QuickFind.h"
#include "WQUPC.h"
#include "UnionFind.h"
#include <iostream>
#include <memory>

int main() {
	std::cout << "Specify number of elements in the grid:" << std::endl;
	auto nr_elements(0);
	if (std::cin >> nr_elements) {

		auto grid = std::shared_ptr<alg::UnionFind>(new alg::WQUPC(nr_elements));

		std::cout << "Specify connected pairs of integers: " << std::endl;
		auto i(0),j(0);
		while(std::cin >> i && std::cin >> j) {
			if(grid->Connected(i, j)) {
				std::cout << "These 2 are already connected! Try again..." << std::endl;
			} else {
				grid->Union(i,j);
				std::cout << "Connected element " << i << " and " << j << std::endl;
			}
		}
	}
	return 0;
}