#include "Point2D.h"
#include "ReadInput.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>

namespace {

const int upperBound = 32767;

Point2D ScalePointToWindow(const Point2D& point) {
	const auto scalingFactorWindow = upperBound / 2;
	const auto translated = TranslateInBothAxis(point, - scalingFactorWindow);
	return CompressByInBothAxis(translated, scalingFactorWindow);
}

void SkipNumberOfPoints(std::istream_iterator<int>& fileContents) {
	++fileContents;
}

std::vector<int> ReadAllCoordinates(std::ifstream& file) {
	std::istream_iterator<int> contents(file);
	SkipNumberOfPoints(contents);
	std::vector<int> coordinates;
	std::copy(contents,
			  std::istream_iterator<int>(),
			  std::back_inserter(coordinates));
	return coordinates;
}

std::vector<Point2D> ConstructPoints(const std::vector<int>& coordinates) {
	std::vector<Point2D> points;
	for(auto xIt = coordinates.cbegin(); xIt != coordinates.cend(); xIt += 2) {
		const auto scaledPoint = ScalePointToWindow(Point2D(*xIt, *(xIt + 1)));
		points.push_back(scaledPoint);
	}
	return points;
}


} // namespace


std::vector<Point2D> ReadInput(const std::string& filename) {
	std::ifstream file(filename);
	if(!file) {
		return {};
	}
	const auto coordinates = ReadAllCoordinates(file);
	return ConstructPoints(coordinates);
}
