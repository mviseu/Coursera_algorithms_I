#include "RandomizedQueue.h"
#include "RandomizedQueueNext.h"
#include <iostream>

int main() {
	RandomizedQueue<int> randomQueue;
	for(auto i = 0; i < 4; ++i) {
		randomQueue.Enqueue(i);
	}

	/*
	for(auto i = 0; i < 9; ++i) {
		std::cout << randomQueue.Dequeue() << std::endl;
	}

	std::cout << randomQueue.Sample() << std::endl;
	*/
	for(auto nexter = randomQueue.CreateNext(); nexter.HasNext(); ) {
		for(auto independentNexter = randomQueue.CreateNext(); independentNexter.HasNext(); ) {
			std::cout << independentNexter.Next() << std::endl;
		}
		std::cout << nexter.Next() << std::endl;
	}
	auto nexter3 = randomQueue.CreateNext();
	while(nexter3.HasNext()) {
		std::cout << "NEXTER3" << std::endl;
		nexter3.Next();
	}
	return 0;
}