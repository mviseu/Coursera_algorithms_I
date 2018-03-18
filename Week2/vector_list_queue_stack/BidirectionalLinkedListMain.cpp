#include "BidirectionalLinkedList.h"
#include <algorithm>
#include <iostream>

int main() {
	BidirectionalLinkedList<int> list;
	for(auto i = 0; i < 20; ++i) {
		list.PushFront(i);
	}
	std::cout << std::endl;	
	for(auto it = list.cbegin(); it != list.cend(); ++it) {
		std::cout << *it << std::endl;
	}
	
	BidirectionalLinkedList<int> reverseList;
	for(auto i = 0; i < 20; ++i) {
		reverseList.PushBack(i);
	}
	std::reverse_copy(list.cbegin(), list.cend(), reverseList.begin());	

	std::cout << std::endl;
	for(const auto& elem : reverseList) {
		std::cout << elem << std::endl;
	}
	return 0;
}