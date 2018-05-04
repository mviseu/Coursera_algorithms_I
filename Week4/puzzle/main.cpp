#include "Board.h"
#include "Solver.h"
#include <iostream>
#include <fstream>
#include <iterator>

void PrintSolution(std::ostream& os, const std::vector<Board>& vec) {
	std::ostream_iterator<Board> out(os, "\n");
	std::copy(vec.begin(), vec.end(), out);
}

int main() {
	std::string file;
	std::cout << "Provide filename" << std::endl;
	if(std::cin >> file) {
		std::ifstream in(file);
		if(in) {
			Board initialBoard;
			in >> initialBoard;
			Solver solver(initialBoard);
			const auto solution = solver.Solution();
			PrintSolution(std::cout, solution);
			std::cout << "Minimum number of moves: " << solver.Moves() << std::endl;
		} else {
			std::cout << "Must provide a valid file!" << std::endl;
		}
	}
	return 0;
}
