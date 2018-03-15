#include <iterator>
#include <iostream>
#include <sstream>
#include <unordered_map>

int main() {
	
	std::istringstream is("Hello this is an experiment");
	std::istream_iterator<char> it(is);
	std::istream_iterator<char> it2(is);
	std::string s;

	is >> s;
	std::cout << s << std::endl;

	
	std::cout << *it << std::endl;
	std::cout << *it++ << std::endl;
	std::cout << *it << std::endl;

	std::cout << *it2++ << std::endl;
	std::cout << *it2 << std::endl;
	
	/*conclusion: 
	when is is consumed, it is updated*/

	std::unordered_map<int, std::string> unordered = {{0, "hello"}, {1, "World"}, {6, "Again"}, {7, "Hi"}};
	for(auto it = unordered.begin(); it != unordered.end(); ++it) {
		for(auto it2 = unordered.begin(); it2 != unordered.end(); ++it2) {
			std::cout << it2->second << std::endl;
		}
		
		std::cout << it->second << std::endl;
	}
	return 0;
}