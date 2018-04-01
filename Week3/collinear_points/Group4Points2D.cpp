#include "Group4Points2D.h"
#include "BottomUpMergeSort.h"
#include <iostream>
#include <cassert>
#include <cmath>

namespace {
bool Near(float expected, float actual, float epsilon = 1E-08) {
	return std::abs(expected - actual) < epsilon;  
}

} // namespace

Group4Points2D::Group4Points2D(const std::vector<Point2D>& pointsIn) : m_points(pointsIn) {
	assert(m_points.size() == nrPoints);
}

bool Group4Points2D::AreCollinear() const {
	const auto firstPoint = m_points[0];
	const auto slope = firstPoint.SlopeTo(m_points[1]);
	return Near(slope, firstPoint.SlopeTo(m_points[2])) && Near(slope, firstPoint.SlopeTo(m_points[3]));
}

std::optional<Line2D> Group4Points2D::GetCollinearLine() const {
	if(!AreCollinear()) {
		return std::nullopt;
	}
	auto sortedLine = m_points;
	BottomUpMergeSort<std::vector<Point2D>::iterator>(sortedLine.begin(), sortedLine.end());
	return Line2D(sortedLine.front(), sortedLine.back());
}