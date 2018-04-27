#include "PriorityQueue.h"
#include <functional>
#include <iostream>


int main() {
	const auto vec = std::vector<int>({6, 2, 90, 15, 53, 4, 5});
	PriorityQueue<int> pq(std::less<int>(), vec);
	PriorityQueue<int> pqEmpty;
	while(!pq.Empty()) {
		std::cout << "Top: " << pq.Top() << std::endl;
		pq.Pop();
	}
	auto i = 0;
	while(pqEmpty.Size() < 10) {
		pqEmpty.Push(i++);
		std::cout << "Empty Top: " << pqEmpty.Top() << std::endl;
	}
	return 0;
}
