#pragma once
#include "UnionFind.h"
#include "WQUPC.h"
#include <memory>

namespace perc {


class Percolation {
public:
	Percolation(int n);
	bool IsOpen(int r, int c) const;
	void Open(int r, int c);
	int NrOpenSites() const;
	bool IsFull(int r, int c) const;
	bool Percolates() const;

private:
	//cannot use bitset since n is not known at compile time
	int GetN() const;
	std::vector<bool> m_openSites;
	std::shared_ptr<alg::UnionFind> m_uf;
};

} // namespace