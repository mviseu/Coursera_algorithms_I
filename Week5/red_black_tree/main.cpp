#include "RedBlackTree.h"
#include <iostream>
#include <string>
#include "Optional.h"

void FindReport(const RedBlackTree<std::string, int>& tree, const std::string& key) {
	const auto find = tree.Find(key);
	if(find) {
		std::cout << "Key " << key << " found." 
				  << "Value is " << (*find).second << std::endl;
	} else {
		std::cout << "Key " << key << " not found." << std::endl;
	}
}

int main() {
	RedBlackTree<std::string, int> tree;
	tree.Insert(std::make_pair(std::string("S"), 3));
	tree.Insert(std::make_pair(std::string("E"), 37));
	tree.Insert(std::make_pair(std::string("A"), 53));
	tree.Insert(std::make_pair(std::string("R"), 743));
	tree.Insert(std::make_pair(std::string("C"), 37));
	tree.Insert(std::make_pair(std::string("H"), 35));
	tree.Insert(std::make_pair(std::string("X"), 1));
	tree.Insert(std::make_pair(std::string("M"), 2));
	tree.Insert(std::make_pair(std::string("P"), 56));
	tree.Insert(std::make_pair(std::string("L"), 6));
	

	FindReport(tree, std::string("aaX"));
	FindReport(tree, std::string("E"));
	FindReport(tree, std::string("A"));
	FindReport(tree, std::string("R"));
	FindReport(tree, std::string("C"));
	FindReport(tree, std::string("H"));
	FindReport(tree, std::string("X"));
	FindReport(tree, std::string("M"));
	FindReport(tree, std::string("P"));
	FindReport(tree, std::string("L"));
	FindReport(tree, std::string("p"));
	return 0;
}
