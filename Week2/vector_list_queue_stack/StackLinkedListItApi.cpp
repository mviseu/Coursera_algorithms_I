#include "StackLinkedList.h"
#include <iostream>
#include <vector>

int main() {
	/*
	StackLinkedList<int> stack;
	StackLinkedList<int>::iterator it = stack.begin();
	if(it == stack.end()) {
		std::cout << "It is at end of stack" << std::endl;
	}
	StackLinkedList<int>::const_iterator cit = stack.cbegin();
	if(it == stack.end()) {
		std::cout << "begin is end" << std::endl;
	}

	StackLinkedList<int>::const_iterator citConvert = stack.begin();


	if(citConvert == cit) {
		std::cout << "same iterator" << std::endl;
	}

	if(citConvert != cit) {
		std::cout << "different iterator" << std::endl;
	}

	std::vector<int> vec;
	if(vec.begin() == vec.end()) {;};

	StackLinkedList<int> nonConstStack;
	if(nonConstStack.begin() == nonConstStack.end()) {;}
	*/

	//non viable conversion/construction

	//StackLinkedList<const int> constStack;

	//StackLinkedList<const int> attemptCopy(std::move(stack));


	//std::vector<int> vecInt = {0,1};
	//std::vector<int>::iterator vecNonConst= vecInt.cbegin();	


	//StackLinkedList<int> stackInt;
	//StackLinkedList<int>::iterator vecNonConst = stackInt.cbegin();

	//StackLinkedList<int>::const_iterator citConvert = stack.begin();

	StackLinkedList<int> stack;
	for(auto i = 0; i < 10; ++i) {
		stack.Push(i);
	}

	
	StackLinkedList<int>::iterator it2 = stack.begin();

	while(it2 != stack.end()) {
		std::cout << *it2++ << std::endl;
	}


	StackLinkedList<std::vector<int>> stackVec;
	stackVec.Push(std::vector<int>({1}));

	StackLinkedList<std::vector<int>>::const_iterator it3 = stackVec.cbegin();

	while(it3 != stackVec.cend()) {
		std::cout << it3->size() << std::endl;
		++it3;
	}
	
	auto it4 = stack.begin();
	*it4 = 3;

	auto it5 = ++stack.begin();
	*it5 = 42;

	std::cout << "BEFORE" << std::endl;
	std::cout << "it4: " << *it4 << std::endl;
	std::cout << "it5: " << *it5 << std::endl;

	swap(it4, it5);

	std::cout << "AFTER" << std::endl;
	std::cout << "it4: " << *it4 << std::endl;
	std::cout << "it5: " << *it5 << std::endl;

	return 0;
}