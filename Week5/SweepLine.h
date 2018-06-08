#pragma once
#include "OrthogonalLineSegment.h"
#include "Point.h"
#include <vector>

std::vector<Point> SweepLine(const std::vector<OrthogonalLineSegment>& lines);