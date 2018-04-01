#pragma once
#include "Point2D.h"
#include "Line2D.h"
#include <vector>

class BruteCollinearPoints {
public:
BruteCollinearPoints(const std::vector<Point2D>& points);
int NumberOfSegments() const;
std::vector<Line2D> Segments() const;
size_t Size() const {return m_points.size();}

private:
std::vector<Point2D> m_points;
};
