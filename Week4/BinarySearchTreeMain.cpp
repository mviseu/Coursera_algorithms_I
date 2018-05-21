#include "BinarySearchTree.h"
#include "BinarySearchTreeIt.h"
#include <iostream>
#include <string>

int main() {
	BinarySearchTree<std::string, int> dict;
	dict.Insert(std::make_pair(std::string("Hello"), 33));
	dict.Insert(std::make_pair(std::string("Bye"), 60));
	dict.Insert(std::make_pair(std::string("This"), 40));
	dict.Insert(std::make_pair(std::string("is"), 55));
	dict.Insert(std::make_pair(std::string("a"), 33));
	for(auto it = dict.Begin(); it != dict.End(); ++it) {
		std::cout << it->first << std::endl;
	}
	return 0;
}

