#include "RandomizedQueue.h"
#include "RandomizedQueueNext.h"
#include <iostream>

int main() {
	RandomizedQueue<int> randomQueue;
	randomQueue.Enqueue(42);
	randomQueue.Enqueue(3);
	randomQueue.Enqueue(1000);

	/*
	for(auto i = 0; i < 9; ++i) {
		std::cout << randomQueue.Dequeue() << std::endl;
	}

	std::cout << randomQueue.Sample() << std::endl;
	*/
	/*
	const RandomizedQueue<int> copyRandomQueue(randomQueue);
	for(auto nexter = copyRandomQueue.CreateNext(); nexter.HasNext(); ) {
		for(auto independentNexter = copyRandomQueue.CreateNext(); independentNexter.HasNext(); ) {
			std::cout << independentNexter.Next() << std::endl;
		}
		std::cout << nexter.Next() << std::endl;
	}
	*/
	auto nextChange = randomQueue.CreateNext();
	std::cout << nextChange.Next() << std::endl;

	randomQueue.Enqueue(6);
	randomQueue.Dequeue();

	while(nextChange.HasNext()) {
		std::cout << nextChange.Next() << std::endl;;
	}


	return 0;
}