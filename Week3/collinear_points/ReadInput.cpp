#include "Point2D.h"
#include "ReadInput.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>

namespace {

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
	for(const auto& coord : coordinates) {
		std::cout << coord << std::endl;
	}
	return coordinates;
}

std::vector<Point2D> ConstructPoints(const std::vector<int>& coordinates) {
	std::vector<Point2D> points;
	for(auto xIt = coordinates.cbegin(); xIt != coordinates.cend(); xIt += 2) {
		std::cout << "x: " << *xIt << " y: " << *(xIt+1) << std::endl;
		points.push_back(Point2D(*xIt, *(xIt + 1)));
	}
	return points;
}


} // namespace


std::vector<Point2D> ReadInput(const std::string& filename) {
	std::ifstream file(filename);
	if(!file) {
		std::cout << "Failed to open " << filename;
		return {};
	}
	const auto coordinates = ReadAllCoordinates(file);
	return ConstructPoints(coordinates);
}
