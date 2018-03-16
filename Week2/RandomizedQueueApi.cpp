#include "RandomizedQueue.h"
#include "RandomizedQueueNext.h"
#include <iostream>

void GetOutScope(std::unique_ptr<RandomizedQueueNext<int>> &uniqueNext) {
	std::cout << "GetScope begin" << std::endl;
	RandomizedQueue<int> randomQueue;
	randomQueue.Enqueue(42);
	randomQueue.Enqueue(3);
	randomQueue.Enqueue(1000);
	uniqueNext = std::make_unique<RandomizedQueueNext<int>>(randomQueue.CreateNext());
}

int main() {
	/*
	RandomizedQueue<int> randomQueue;
	randomQueue.Enqueue(42);
	randomQueue.Enqueue(3);
	randomQueue.Enqueue(1000);
	*/

	/*std::cout << randomQueue.Sample() << std::endl;
	
	const RandomizedQueue<int> copyRandomQueue(randomQueue);
	for(auto nexter = copyRandomQueue.CreateNext(); nexter.HasNext(); ) {
		for(auto independentNexter = copyRandomQueue.CreateNext(); independentNexter.HasNext(); ) {
			std::cout << independentNexter.Next() << std::endl;
		}
		std::cout << nexter.Next() << std::endl;
	}
	*/
	/*
	auto next2 = randomQueue.CreateNext();
	std::cout << next2.Next() << std::endl;
	//randomQueue.Dequeue();
	//randomQueue.Enqueue(5);
	next2.Next();
	next2.Next();
	*/

	/*auto nextChange = randomQueue.CreateNext();
	std::cout << nextChange.Next() << std::endl;

	randomQueue.Enqueue(6);
	randomQueue.Dequeue();

	while(nextChange.HasNext()) {
		std::cout << nextChange.Next() << std::endl;;
	}
	*/

	/*
	Vector<int> vec;
	Vector<int> vecSimilar;

	vec.PushBack(1);
	vec.PushBack(2);

	std::cout << std::hash<Vector<int>>()(vec) << std::endl;

	vecSimilar.PushBack(2);
	vecSimilar.PushBack(1);

	std::cout << std::hash<Vector<int>>()(vecSimilar) << std::endl;
	*/

	std::unique_ptr<RandomizedQueueNext<int>> uptr = nullptr;
	GetOutScope(uptr);

	//uptr->Next();
	//uptr->HasNext();

	return 0;
}
