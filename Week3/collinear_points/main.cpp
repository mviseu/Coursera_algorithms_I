#include "Draw.h"
#include "ReadInput.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
	std::cout << "Provide filename" << std::endl;
	std::string inputFileName;
	std::cin >> inputFileName;
	const auto points = ReadInput(inputFileName);


	Draw& window = Draw::GetDraw();
	while (!window.ShouldWindowClosePoll()) {
		window.AddScaledPoint2D(Point2D(-1, 1));
		window.AddScaledPoint2D(Point2D(1, 1));
		window.AddScaledLine2D(Line2D(Point2D(-1, -1), Point2D(1, 1)));
	}
	return 0;
}
