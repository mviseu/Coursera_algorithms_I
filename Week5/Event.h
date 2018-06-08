#pragma once
#include "VerticalLineYy.h"
#include <variant>

struct Event {
	Event(double xCoord, const std::variant<double, VerticalLineYy>& yyCoord) : x(xCoord), yy(yyCoord) {}
	double x{0};
	std::variant<double, VerticalLineYy> yy;
};

bool IsEventPartOfHorizontalLine(const Event& event);
bool IsEventVerticalLine(const Event& event);

bool operator<(const Event& lhs, const Event& rhs);
bool operator>(const Event& lhs, const Event& rhs);
bool operator<=(const Event& lhs, const Event& rhs);
bool operator>=(const Event& lhs, const Event& rhs);