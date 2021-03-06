#include "BinarySearchTree.h"
#include "BinarySearchTreeIt.h"
#include "Range.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <map>

void InsertNewPair(BinarySearchTree<std::string, int>& map, const std::string& key, int val) {
	auto pairIt = map.Insert(std::make_pair(key, val));
	std::cout << pairIt.first->first << " Inserted: " << pairIt.second << std::endl;
}

void ReportAllRanks(const BinarySearchTree<std::string, int>& map) {
	for(auto it = map.Begin(); it != map.End(); ++it) {
		std::cout << it->first << std::endl;
		std::cout << "Rank is:" << map.Rank(it->first) << std::endl;
	}
}

void ReportReverseRanks(const BinarySearchTree<std::string, int>& map) {
	for(auto revIt = map.RBegin(); revIt != map.REnd(); ++revIt) {
		std::cout << "Reverse rank is: " << map.Rank(revIt->first) << std::endl;
	}
}

void ReportRangeCount(const std::string& lo, const std::string& hi, const BinarySearchTree<std::string, int>& mp) {
	Range<std::string> rg(lo, hi);
	std::cout << "RangeCount between " << lo << " and " 
			  << hi << " is: " << mp.RangeCount(rg) << std::endl;
}

template<typename Key>
void PrintKeys(const std::vector<Key>& keys) {
	std::ostream_iterator<Key>os(std::cout, "\n");
	std::copy(keys.begin(), keys.end(), os);
}

void ReportRangeSearch(const std::string& lo, const std::string& hi, const BinarySearchTree<std::string, int>& mp) {
	Range<std::string> rg(lo, hi);

	std::cout << "RangeSearch between " << lo << " and " 
			  << hi << " is: " << std::endl;
	PrintKeys(mp.RangeSearch(rg));
	std::cout << std::endl;
}

int main() {
	BinarySearchTree<std::string, int> dict;
	InsertNewPair(dict, "Hello", 33);
	InsertNewPair(dict, "Bye", 60);
	InsertNewPair(dict, "This", 40);
	InsertNewPair(dict, "is", 55);
	InsertNewPair(dict, "x", 6);
	InsertNewPair(dict, "a", 33);

	ReportRangeCount("Hello", "is", dict);
	ReportRangeCount("Hallo", "is", dict);
	ReportRangeCount("Hello", "isnt", dict);
	ReportRangeCount("Hallo", "isnt", dict);
	ReportRangeCount("A", "z", dict);

	ReportRangeSearch("Hello", "is", dict);
	ReportRangeSearch("Hallo", "is", dict);
	ReportRangeSearch("Hello", "isnt", dict);
	ReportRangeSearch("Hallo", "isnt", dict);
	ReportRangeSearch("A", "z", dict);
	ReportRangeSearch("Hello", "Hello", dict);
	ReportRangeSearch("y", "z", dict);

	std::cout << "End Report Range Search" << std::endl;

	ReportAllRanks(dict);
	std::cout << "Reverse" << std::endl;
	ReportReverseRanks(dict);
	
	dict.Erase(dict.Find("Hello"));
	ReportAllRanks(dict);

	dict.Erase(dict.Find("Bye"));
	ReportAllRanks(dict);

	dict.Erase(dict.Find("This"));
	ReportAllRanks(dict);

	dict.Erase(dict.Find("is"));
	ReportAllRanks(dict);

	dict.Erase(dict.Find("a"));
	ReportAllRanks(dict);

	dict.Erase(dict.Find("x"));
	ReportAllRanks(dict);


	return 0;
}

