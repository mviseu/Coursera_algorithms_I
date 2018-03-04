#include "StackArray.h"
#include "StackLinkedList.h"
#include "StackResizeArray.h"
#include <memory>
#include <iostream>

int main() {
/*
	auto stack1 = std::unique_ptr<Stack<int>>(std::make_unique<StackArray<int>>(100).release());
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
*/

/* 
	auto stack1 = std::unique_ptr<Stack<int>>(std::make_unique<StackLinkedList<int>>(0).release());
	stack1->Push(1);	
	stack1->Push(2);
	stack1->Push(3);
	stack1->Push(4);
	stack1->Push(5);
	
	StackLinkedList<int> def(100);
	StackLinkedList<int> stack2(def);
	stack2 = def;
	StackLinkedList<int> stack3(std::move(stack2));
	while(!stack3.IsEmpty()) {
		std::cout << stack3.Top() << std::endl;
		stack3.Pop();
	}
	//stack3 = StackLinkedList<int>();
	while(!stack1->IsEmpty()) {
		std::cout << stack1->Top() << std::endl;
		stack1->Pop();
	}

	auto stack4 = StackLinkedList<int>(0);
	stack4.Push(42);	
	stack4.Push(3);

	stack3 = std::move(stack4);
	while(!stack3.IsEmpty()) {
		std::cout << stack3.Top() << std::endl;
		stack3.Pop();
	}
*/

	auto stack1 = std::unique_ptr<Stack<int>>(std::make_unique<StackResizeArray<int>>().release());
	
	stack1->Push(1);
	stack1->Push(2);
	stack1->Push(3);
	stack1->Push(4);
	stack1->Push(5);
	
	StackResizeArray<int> def;
	StackResizeArray<int> stack2(def);
	stack2 = def;
	StackResizeArray<int> stack3(std::move(stack2));


	while(!stack1->IsEmpty()) {
		std::cout << stack1->Top() << std::endl;
		stack1->Pop();
	}

	auto stack4 = StackResizeArray<int>();
	stack4.Push(42);	
	stack4.Push(3);

	stack3 = std::move(stack4);
	while(!stack3.IsEmpty()) {
		std::cout << stack3.Top() << std::endl;
		stack3.Pop();
	}
	return 0;

}