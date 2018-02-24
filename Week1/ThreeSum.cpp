#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

std::vector<std::tuple<int, int, int>> ThreeSum(const std::vector<int>& input) {
	std::vector<std::tuple<int, int, int>> ret;
	std::vector<int> sortedInput(input);
	std::sort(sortedInput.begin(), sortedInput.end());
	for(auto it = sortedInput.cbegin(); it < sortedInput.cend() - 2; ++it) {
		if(it == sortedInput.cbegin() || *it != *(it - 1)) {
			auto start = it + 1;
			auto end = sortedInput.cend() - 1;
			while(start < end) {
				if(*it + *start + *end == 0) {
					ret.push_back(std::make_tuple(*it, *start, *end));
				}
				if(*it + *start + *end < 0) {
					++start;
					while(start < end && *start == *(start - 1)) {
						++start;
					}
				} else {
					--end;
					while(start < end && *end == *(end + 1)) {
						--end;
					}
				}
			}
		}
	}
	return ret;
}

int main() {
	std::vector<int> vec = {-2, -2, -2, -2, -2, -1, -1, -1, -1, -1, 0, -3, 1, 1, 1, 1, 1, -4, 2, 3};
	auto solutions = ThreeSum(vec);
	for(const auto&sol : solutions) {
		std::cout << std::get<0>(sol) << std::endl;
		std::cout << std::get<1>(sol) << std::endl;
		std::cout << std::get<2>(sol) << std::endl;
		std::cout << std::endl;
	}
	return 0;
}