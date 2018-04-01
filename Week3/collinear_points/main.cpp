#include "BruteCollinearPoints.h"
#include "Draw.h"
#include "ReadInput.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace {

std::vector<Point2D> ReadPoints() {
	std::cout << "Provide filename" << std::endl;
	std::string inputFileName;
	std::cin >> inputFileName;
	return ReadInput(inputFileName);		
}

void DrawPoints(const std::vector<Point2D>& points, Draw& window) {
	std::for_each(points.cbegin(), points.cend(), [&window](const Point2D& point) {
		window.AddScaledPoint2D(point);
	});
}

void DrawCollinearSegments(const std::vector<Line2D>& lines, Draw& window) {
	std::for_each(lines.cbegin(), lines.cend(), [&window](const Line2D& line) {
		window.AddScaledLine2D(line);
	});
}

} // namespace

int main() {
	const auto points = ReadPoints();
	const auto lines = BruteCollinearPoints{points}.Segments();
	Draw& window = Draw::GetDraw();
	while (!window.ShouldWindowClosePoll()) {
		DrawPoints(points, window);
		DrawCollinearSegments(lines, window);
	}
	return 0;
}
