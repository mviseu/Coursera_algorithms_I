#pragma once
#include "Line2D.h"
#include "Point2D.h"

class FastCollinearPoints {
public:
FastCollinearPoints(const std::vector<Point2D>& points);
int NumberOfSegments() const;
std::vector<Line2D> Segments() const;

private:
std::vector<Point2D> m_points;
};