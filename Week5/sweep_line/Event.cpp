#include "Event.h"

bool IsEventPartOfHorizontalLine(const Event& event) {
	return std::holds_alternative<double>(event.yy);
}

bool IsEventVerticalLine(const Event& event) {
	return !IsEventPartOfHorizontalLine(event);
}

bool operator<(const Event& lhs, const Event& rhs) {
	return lhs.x < rhs.x;
}

bool operator>=(const Event& lhs, const Event& rhs) {
	return !(lhs < rhs);
}

bool operator>(const Event& lhs, const Event& rhs) {
	return rhs < lhs;
}

bool operator<=(const Event& lhs, const Event& rhs) {
	return !(rhs < lhs);
}