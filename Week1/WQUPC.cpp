#include "WQUPC.h"
#include <algorithm>
#include <iterator>
#include <utility>


namespace alg {

WQUPC::WQUPC(const int n) : UnionFind() {
	int j{0};
	constexpr int initTreeSize = 1;
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

void WQUPC::ConnectSmallToLarge(int rootSmall, int rootLarge) {
	m_connectedTo[rootSmall] = rootLarge;
	m_sizeOfTree[rootLarge] += m_sizeOfTree[rootSmall];
}

void WQUPC::Union(int p, int q) {
	auto rootp = Root(p);
	auto rootq = Root(q);
	if(rootp != rootq) {
		m_sizeOfTree[rootp] > m_sizeOfTree[rootq] ? ConnectSmallToLarge(rootq, rootp) : ConnectSmallToLarge(rootp, rootq);
	}
}

} // namespace alg