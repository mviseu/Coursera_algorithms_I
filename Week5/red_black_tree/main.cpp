#include "RedBlackTree.h"
#include <iostream>
#include <string>

int main() {
	RedBlackTree<std::string, int> tree;
	tree.Insert(std::make_pair(std::string("S"), 3));
	tree.Insert(std::make_pair(std::string("E"), 3));
	tree.Insert(std::make_pair(std::string("A"), 3));
	tree.Insert(std::make_pair(std::string("R"), 3));
	tree.Insert(std::make_pair(std::string("C"), 3));
	tree.Insert(std::make_pair(std::string("H"), 3));
	tree.Insert(std::make_pair(std::string("X"), 3));
	tree.Insert(std::make_pair(std::string("M"), 3));
	tree.Insert(std::make_pair(std::string("P"), 3));
	tree.Insert(std::make_pair(std::string("L"), 3));
	return 0;
}
