#include <iostream>

struct Test {
Test() {Fn();}
void Fn() const {std::cout << "const" << std::endl;}
void Fn() {std::cout << "non const" << std::endl;}

int i{0};
};

int main() {
	auto t = Test();
	return 0;
}