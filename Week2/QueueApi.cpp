#include "Queue.h"
#include "QueueResizeArray.h"
#include <iostream>

int main() {
	QueueResizeArray<int> queue;
	std::cout << queue;
	for(auto i = 0; i < 10; ++i) {
		queue.Enqueue(i);
		std::cout << queue;
	}
	for(auto i = 0; i < 10; ++i) {
		queue.Dequeue();
		std::cout << queue;
	}
	return 0;
}