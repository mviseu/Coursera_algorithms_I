#pragma once

struct Point2D {
	Point2D() = default;
	Point2D(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}
	int x{0};
	int y{0};
};