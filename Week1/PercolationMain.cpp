#include "Percolation.h"
#include <iostream>

int main() {
	auto perc = perc::Percolation(5);
	std::cout << perc.IsOpen(1,2) << std::endl;
	std::cout << perc.IsOpen(5,5) << std::endl;
	std::cout << perc.IsOpen(2,3) << std::endl;
	return 0;
}