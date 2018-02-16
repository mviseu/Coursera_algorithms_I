#include "WQUPC.h"
#include <algorithm>
#include <iterator>

namespace alg {
WQUPC::WQUPC(const int n) : UnionFind() {
	int j{0};
	const int initTreeSize = 1;
	std::generate_n(std::back_inserter(m_connectedTo), n, [j] () mutable {return j++;});
	std::fill_n(std::back_inserter(m_sizeOfTree), n, initTreeSize);
}

int WQUPC::Root(int i) {
	while(i != m_connectedTo[i]) {
		m_connectedTo[i] = m_connectedTo[m_connectedTo[i]];
		i = m_connectedTo[i];
	}
	return i;
}

bool WQUPC::Connected(int p, int q) {
	return Root(p) == Root(q);
}


void WQUPC::Union(int p, int q) {
	auto rootp = Root(p);
	auto rootq = Root(q);
	if(rootp != rootq) {
		if(m_sizeOfTree[rootp] > m_sizeOfTree[rootq]) {
			//point root q to p
			m_connectedTo[rootq] = rootp;
			m_sizeOfTree[rootp] += m_sizeOfTree[rootq];
		} else {
			m_connectedTo[rootp] = rootq;
			m_sizeOfTree[rootq] += m_sizeOfTree[rootp];
		}
	}
}

} // namespace alg