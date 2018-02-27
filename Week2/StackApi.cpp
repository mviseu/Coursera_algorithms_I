#include "StackArray.h"
#include <memory>
#include <iostream>

int main() {
	Stack<int> *stack1 = new StackArray<int>(100);
	
	stack1->Push(1);
	
	stack1->Push(2);
	stack1->Push(3);
	stack1->Push(4);
	stack1->Push(5);
	
	StackArray<int> def;
	StackArray<int> stack2(def);
	stack2 = def;
	StackArray<int> stack3((StackArray<int>()));
	stack3 = StackArray<int>();
	while(!stack1->IsEmpty()) {
		std::cout << stack1->Top() << std::endl;
		stack1->Pop();
	}

	delete stack1;
	
	return 0;
}