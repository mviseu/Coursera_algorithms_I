#include "VerticalLineYy.h"

double GetLowerLimit(const VerticalLineYy& line) {
	return line.y1 < line.y2 ? line.y1 : line.y2;
}

double GetUpperLimit(const VerticalLineYy& line) {
	return line.y1 == GetLowerLimit(line) ? line.y2 : line.y1;
}