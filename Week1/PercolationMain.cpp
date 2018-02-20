#include "PercolationStats.h"
#include <iostream>

int main() {
	std::cout << "Welcome to the program percolation!" << std::endl;
	std::cout << "Start by specifying the number of sites(n):" << std::endl;
	int n = 0;
	if(std::cin >> n) {
		std::cout << "Now specify the number of trials:" << std::endl;
	}
	int trials = 9;
	if (std::cin >> trials) {
		auto stats = perc::PercolationStats(n, trials);
		stats.PrintStats(std::cout);
	}
	return 0;
}