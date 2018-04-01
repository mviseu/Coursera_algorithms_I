#include "BruteCollinearPoints.h"
#include "Group4Points2D.h"
#include <algorithm>
#include <stdexcept>


BruteCollinearPoints::BruteCollinearPoints(const std::vector<Point2D>& points) {
	std::vector<Point2D> m_points;
	std::for_each(points.cbegin(), points.cend(), [&m_points](const Point2D& point) {
		if(std::find(m_points.cbegin(), m_points.cend(), point) == m_points.cend()) {
			throw std::invalid_argument("Repeated points cannot be supplied as arguments");
		}
		m_points.push_back(point);
	});
}

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