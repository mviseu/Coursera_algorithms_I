#include "Partition.h"
#include <algorithm>
#include <vector>

int main() {
	std::vector<int> vec = {1};
	Partition(vec.begin(), vec.end(), [](int i) {return !(1 < i);});
	for(const auto& elem : vec) {
		std::cout << elem << std::endl;
	}
	return 0;
}