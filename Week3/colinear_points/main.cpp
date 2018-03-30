#include "Draw.h"
#include <iostream>
#include <vector>

int main() {
	Draw window;

	while (!window.ShouldWindowClosePoll()) {
		window.AddScaledPoint2D(Point2D(-1, 1));
		window.AddScaledPoint2D(Point2D(1, 1));
		window.AddScaledLine2D(Line2D(Point2D(-1, -1), Point2D(1, 1)));
	}
	return 0;
}
