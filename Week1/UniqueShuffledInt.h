#pragma once
#include <algorithm>
#include <iterator>
#include <random>
#include <ctime>
#include <vector>

namespace math {

struct UniqueShuffledInt {
	UniqueShuffledInt(int lb, int ub) {
		int j = 0;
		std::generate_n(std::back_inserter(vec), ub - lb + 1, [j]() mutable {return j++;});
		std::random_shuffle(vec.begin(), vec.end());
		it = vec.cbegin();
	}

	int operator()() {
		if(it == vec.cend()) {
			it = vec.cbegin();
		}
		return *(it++);
	};

private:
	std::vector<int> vec;
	std::vector<int>::const_iterator it;
};

} // namespace math