#pragma once
#include "Line2D.h"
#include "Point2D.h"
#include <optional>
#include <vector>

constexpr const auto nrPoints = 4;

class Group4Points2D {
public:
	Group4Points2D(const std::vector<Point2D>& pointsIn) : m_points(pointsIn) {}
	std::optional<Line2D> GetCollinearLine() const;
private:
	bool AreCollinear() const;
	std::vector<Point2D> m_points;
};