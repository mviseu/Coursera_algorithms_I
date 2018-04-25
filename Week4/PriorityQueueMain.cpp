#include "PriorityQueue.h"
#include <functional>
#include <iostream>


int main() {
	const auto vec = std::vector<int>({6, 2, 90, 15, 53, 4, 5});
	PriorityQueue<int> pq(std::less<int>(), vec);
	return 0;
}