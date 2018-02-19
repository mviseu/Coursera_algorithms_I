#include "Percolation.h"
#include <iostream>

int main() {
	std::cout << "Type size N" << std::endl;
	int n = 0;
	if (std::cin >> n) {
		auto perc = perc::Percolation(n);
		perc.Run();
	}
	return 0;
}