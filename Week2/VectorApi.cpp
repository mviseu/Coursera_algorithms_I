#include "Vector.h"
#include "RandomizedQueue.h"
#include <iostream>

int main() {
	Vector<int> vec;
	for(auto i = 0; i < 10; ++i) {
		vec.PushBack(i);
	}
	std::cout << vec[5] << std::endl;
	vec[5] = 42;
	std::cout << vec[5] << std::endl;
	const Vector<int> constVec(vec);
	std::cout << constVec[7] << std::endl;
	std::cout << constVec[9] << std::endl;
	std::cout << constVec[0] << std::endl;
	return 0;
}