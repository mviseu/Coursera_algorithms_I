#include "BinarySearchTree.h"
#include "BinarySearchTreeIt.h"
#include <iostream>
#include <string>

int main() {
	BinarySearchTree<std::string, int> dict;
	auto pairHell = dict.Insert(std::make_pair(std::string("Hello"), 33));
	std::cout << pairHell.first->first << " inserted: " << pairHell.second << std::endl;

	auto pairBye = dict.Insert(std::make_pair(std::string("Bye"), 60));
	std::cout << pairBye.first->first << " inserted: " << pairBye.second << std::endl;

	auto pairThis = dict.Insert(std::make_pair(std::string("This"), 40));
	std::cout << pairThis.first->first << " inserted: " << pairThis.second << std::endl;

	auto pairIs = dict.Insert(std::make_pair(std::string("is"), 55));
	std::cout << pairIs.first->first << " inserted: " << pairIs.second << std::endl;

	auto pairx = dict.Insert(std::make_pair(std::string("x"), 6));
	std::cout << pairx.first->first << " inserted: " << pairx.second << std::endl;

	auto paira = dict.Insert(std::make_pair(std::string("a"), 33));
	std::cout << paira.first->first << " inserted: " << paira.second << std::endl;

	pairHell = dict.Insert(std::make_pair(std::string("Hello"), 100));
	std::cout << pairHell.first->first << " inserted: " << pairHell.second << " value: " << pairHell.first->second << std::endl;
	for(auto it = dict.Begin(); it != dict.End(); ++it) {
		std::cout << it->first << std::endl;
	}
	return 0;
}

