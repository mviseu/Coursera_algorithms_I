#include "OrthogonalLineSegment.h"

bool IsLineHorizontal(const OrthogonalLineSegment& line) {
	return line.start.y == line.end.y;
}

bool IsLineVertical(const OrthogonalLineSegment& line) {
	return line.start.x == line.end.x;
}