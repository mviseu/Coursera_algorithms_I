#include "Group4Points2D.h"
#include "BottomUpMergeSort.h"

bool Group4Points2D::AreCollinear() const {
	auto firstPoint = m_points[0];
	return firstPoint.SlopeTo(m_points[1]) == firstPoint.SlopeTo(m_points[2]) == firstPoint.SlopeTo(m_points[3]);
}

std::optional<Line2D> Group4Points2D::GetCollinearLine() const {
	if(!AreCollinear()) {
		return std::nullopt;
	}
	auto sortedLine = m_points;
	BottomUpMergeSort<std::vector<Point2D>::iterator>(sortedLine.begin(), sortedLine.end(), std::less<Point2D>());
	return Line2D(*sortedLine.begin(), *sortedLine.end());
}