#include "BottomUpMergeSort.h"
#include "FastCollinearPoints.h"
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <vector>

namespace {

std::vector<Point2D> SortBySlopes(const Point2D& base, const std::vector<Point2D>& unsortedPoints) {
	std::vector<Point2D> sortedSlopes = unsortedPoints;
	BottomUpMergeSort(sortedSlopes.begin(), sortedSlopes.end(), [&base](const Point2D& lhs, const Point2D& rhs) {
		return SlopeOrder(base, lhs, rhs);
	});
	return sortedSlopes;
}
struct CollinearLine {
	int nrPoints{0};
	Point2D min;
	Point2D max;
};

Point2D UpdateMin(const Point2D& minSoFar, const Point2D& candidate) {
	return candidate < minSoFar ? candidate : minSoFar;
}

Point2D UpdateMax(const Point2D& maxSoFar, const Point2D& candidate) {
	return candidate > maxSoFar ? candidate : maxSoFar;
}

CollinearLine AddPointOfSameSlope(CollinearLine&& line, const Point2D& newPoint) {
	return CollinearLine({++line.nrPoints, UpdateMin(line.min, newPoint), UpdateMax(line.max, newPoint)});
}

std::vector<Line2D> AddToSegmentsIfCollinear(std::vector<Line2D>&& segments, const CollinearLine& lineCandidate) {
	if(lineCandidate.nrPoints >= 4) {
		segments.push_back(Line2D(lineCandidate.min, lineCandidate.max));
	}
	return std::move(segments);
}

CollinearLine CreateFirstCollinearLine(const Point2D& basePoint, const Point2D& firstPoint) {
	return CollinearLine({2, UpdateMin(basePoint, firstPoint), UpdateMax(basePoint, firstPoint)});
}

bool AreTwoSlopesEqual(const Point2D& base, const Point2D& p, const Point2D& q) {
	return base.SlopeTo(p) == base.SlopeTo(q);
}

std::vector<Line2D> FindCollinearLinesMoreThan2Points(const std::vector<Point2D>& sortedSlopes) {
	std::vector<Line2D> segments;
	const auto basePointIt = sortedSlopes.cbegin();
	const auto firstPointIt = basePointIt + 1;
	auto collinearLine = CreateFirstCollinearLine(*basePointIt, *firstPointIt);
	for(auto pointIt = firstPointIt; pointIt != sortedSlopes.cend() - 1; ++pointIt) {
		auto nextPoint = *(pointIt + 1);
		if(AreTwoSlopesEqual(*basePointIt, *pointIt, nextPoint)) {
			collinearLine = AddPointOfSameSlope(std::move(collinearLine), nextPoint);		
		} else {
			segments = AddToSegmentsIfCollinear(std::move(segments), collinearLine);
			collinearLine = CreateFirstCollinearLine(*basePointIt, nextPoint);
		}
	}
	return AddToSegmentsIfCollinear(std::move(segments), collinearLine);
}

std::vector<Line2D> FindCollinearLines(const std::vector<Point2D>& sortedSlopes) {
	assert(!sortedSlopes.empty());
	if(sortedSlopes.size() > 1) {
		return FindCollinearLinesMoreThan2Points(sortedSlopes);
	} else {
		return {};
	}
}

} // namespace

/* Reuse BruteCollinearPoints initializer */
FastCollinearPoints::FastCollinearPoints(const std::vector<Point2D>& points) {
	std::for_each(points.cbegin(), points.cend(), [this](const Point2D& point) {
		if(std::find(m_points.cbegin(), m_points.cend(), point) != m_points.cend()) {
			throw std::invalid_argument("Repeated points cannot be supplied as arguments");
		}
		m_points.push_back(point);
	});
}

int FastCollinearPoints::NumberOfSegments() const {
	return Segments().size();
}

std::vector<Line2D> FastCollinearPoints::Segments() const {
	std::vector<Line2D> segments;
	for(const auto& point : m_points) {
		const auto sortedSlopes = SortBySlopes(point, m_points); // point slope with itself will always be at front
		const auto newSegments = FindCollinearLines(sortedSlopes);
		segments.insert(segments.end(), newSegments.cbegin(), newSegments.cend());
	}
	return segments;
}