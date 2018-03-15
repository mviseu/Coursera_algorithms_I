#include "RandomIntGenerator.h"
#include <random>
#include <ctime>

int GetRandomInt(int minInclusive, int maxInclusive) {
	static std::default_random_engine e(std::time(nullptr));
	std::uniform_int_distribution<int> ud(minInclusive, maxInclusive);
	return ud(e);
}