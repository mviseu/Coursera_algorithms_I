#include "Line2D.h"
#include <sstream>

Line2D::operator std::string() const {
	std::ostringstream os;
	os << std::string(p) << " -> " << std::string(q);
	return os.str();
}