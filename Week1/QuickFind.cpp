#include "QuickFind.h"
#include <algorithm>
#include <iterator>

namespace alg {

QuickFind::QuickFind(int n)  {
	int j = {0};
	std::generate_n(std::back_inserter(m_connectedTo), n, [j] () mutable {return j++;});
}


bool QuickFind::Connected(int p, int q) const {
	return m_connectedTo[p] == m_connectedTo[q];
}


void QuickFind::Union(int p, int q) {
	auto rootp = m_connectedTo[p];
	auto rootq = m_connectedTo[q];
	std::replace_if(m_connectedTo.begin(), m_connectedTo.end(), [&] (int c) {return c == rootp;}, rootq);
}


} // namespace