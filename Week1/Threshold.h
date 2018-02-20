#pragma once
#include <stdexcept>

namespace perc {

struct Threshold {
	Threshold(double d) {
		if(d < 0 || d > 1) {
			throw std::out_of_range("Percolation threshold is out of range");
		}
		threshold = d;
	} 
	double threshold = 0.0;
};

} // namespace perc