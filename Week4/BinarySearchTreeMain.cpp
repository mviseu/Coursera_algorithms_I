#include "BinarySearchTree.h"
#include "BinarySearchTreeIt.h"
#include <iostream>
#include <string>
#include <map>

int main() {
	BinarySearchTree<std::string, int> dict;
	auto pairHell = dict.insert(std::make_pair(std::string("Hello"), 33));
	std::cout << pairHell.first->first << " inserted: " << pairHell.second << std::endl;
	auto pairBye = dict.insert(std::make_pair(std::string("Bye"), 60));
	std::cout << pairBye.first->first << " inserted: " << pairBye.second << std::endl;
	auto pairThis = dict.insert(std::make_pair(std::string("This"), 40));
	std::cout << pairThis.first->first << " inserted: " << pairThis.second << std::endl;
	auto pairIs = dict.insert(std::make_pair(std::string("is"), 55));
	std::cout << pairIs.first->first << " inserted: " << pairIs.second << std::endl;
	auto pairx = dict.insert(std::make_pair(std::string("x"), 6));
	std::cout << pairx.first->first << " inserted: " << pairx.second << std::endl;
	auto paira = dict.insert(std::make_pair(std::string("a"), 33));
	std::cout << paira.first->first << " inserted: " << paira.second << std::endl;
	pairHell = dict.insert(std::make_pair(std::string("Hello"), 100));
	std::cout << pairHell.first->first << " inserted: " << pairHell.second << " value: " << pairHell.first->second << std::endl;

     
	for(auto it = dict.begin(); it != dict.end(); ++it) {
		std::cout << it->first << std::endl;
	}
	auto eraseIt = dict.find("x");
	dict.erase(eraseIt);

	std::cout << "after erase" << std::endl;
	for(auto it = dict.begin(); it != dict.end(); ++it) {
		std::cout << it->first << std::endl;
	}

	return 0;
}

