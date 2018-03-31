#include "BruteCollinearPoints.h"
#include "Group4Points2D.h"


BruteCollinearPoints::BruteCollinearPoints(const std::vector<Point2D>& points) : m_points(points) {}

std::vector<Line2D> BruteCollinearPoints::Segments() const {
	std::vector<Line2D> collinearLines;
	for(auto i = m_points.cbegin(); i < m_points.cend(); ++i) {
		for(auto j = i + 1; j < m_points.cend(); ++j) {
			for(auto k = j + 1; k < m_points.cend(); ++k) {
				for(auto l = k + 1; l < m_points.cend(); ++l) {
					if(const auto collinearLine = Group4Points2D({*i, *j, *k, *l}).GetCollinearLine()) {
						collinearLines.push_back(*collinearLine);
					}
				}
			}
		}
	}
}

int BruteCollinearPoints::NumberOfSegments() const {
	return Segments().size();
}