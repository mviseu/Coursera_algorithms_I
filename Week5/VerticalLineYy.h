#pragma once

struct VerticalLineYy {
	VerticalLineYy(double yy1, double yy2) : y1(yy1), y2(yy2) {}
	double y1{0};
	double y2{0};
};

double GetLowerLimit(const VerticalLineYy& line);

double GetUpperLimit(const VerticalLineYy& line);