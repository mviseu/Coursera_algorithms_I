#pragma once
#include <random>
#include <ctime>

namespace math {

struct UniformInt {
	UniformInt(int lb, int ub) : m_lowerBound(lb), m_upperBound(ub) {}

	int operator()() const {
		static std::default_random_engine e(std::time(0));
		static std::uniform_int_distribution<int> d(m_lowerBound, m_upperBound);
		return d(e);
	};

private:
	int m_lowerBound{0};
	int m_upperBound{0};
};

} // namespace math