#pragma once
#include "Threshold.h"
#include "UnionFind.h"
#include "WQUPC.h"
#include <memory>
#include <stdexcept>

namespace perc {

struct Threshold;

class Percolation {
public:
	Percolation(int n);
	bool IsOpen(int r, int c) const;
	void Open(int r, int c);
	int NrOpenSites() const;
	bool IsFull(int r, int c) const;
	bool Percolates() const;
	Threshold Run();

private:
	//cannot use bitset since n is not known at compile time
	int GetN() const;

	int m_nrOpenSites = {0};
	std::vector<bool> m_isOpenSite;
	std::shared_ptr<alg::UnionFind> m_uf;
};

} // namespace