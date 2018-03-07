#include "Queue.h"
#include "QueueResizeArray.h"
#include <iostream>

int main() {
	QueueResizeArray<int> queue;
	for(auto i = 0; i < 80000000; ++i) {
		queue.Enqueue(i);
	}
	QueueResizeArray<int> queueCopy(queue);
	QueueResizeArray<int> queueBackup(queue);
	QueueResizeArray<int> queueMove(std::move(queue));

	queueMove = queueBackup;
	queueMove = std::move(queueBackup);

	std::cout << queueMove.First() << std::endl;
	std::cout << queueMove.Last() << std::endl;
	queueMove.Reinitialize();
	/*
	for(auto i = 0; i < 800000000; ++i) {
		queue.Dequeue();
	}
	*/
	/*
	for(auto i = 0; i < 5; ++i) {
		queue.Dequeue();
	}
	for(auto i = 10; i < 12; ++i) {
		queue.Enqueue(i);
	}
	for(auto i = 0; i < 7; ++i) {
		queue.Dequeue();
	}
	*/
	return 0;
}