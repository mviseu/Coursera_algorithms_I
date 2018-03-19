#include <vector>
#include <utility>
#include <iostream>

// Sort array of buckets. Each bucket can have colour red, blue or white. Performance must be O(N). No extra space allowed.
enum class Colour {red, white, blue};

void DutchFlag(std::vector<Colour>& unsortedFlag) {
	auto redBoundary = unsortedFlag.rend();
	auto blueBoundary = unsortedFlag.end();
	auto it = unsortedFlag.begin();
	while(it < blueBoundary) {
		switch(*it) {
		case Colour::red:
			std::swap(*--redBoundary, *(it++));
			break;
		case Colour::blue:
			std::swap(*--blueBoundary, *it);
			break;
		default:
			++it;
			break;
		}
	}
}

int main() {
	std::vector<Colour> vec = {Colour::white, Colour::red, Colour::white, Colour::red, Colour::blue, Colour::red, Colour::blue};
	DutchFlag(vec);
	for(const auto& elem : vec) {
		switch(elem) {
		case Colour::red:
			std::cout << "R" << " ";
			break;
		case Colour::blue:
			std::cout << "B" << " ";
			break;
		default:
			std::cout << "W" << " ";
			break;
		}
		std::cout << std::endl;
	}
	return 0;
}
