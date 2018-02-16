#pragma once
#include "UnionFind.h"
#include <vector>

namespace alg {

class WQUPC : public UnionFind {

public:
explicit WQUPC(int n);
// path compression prevents Connected from being const
virtual bool Connected(int p, int q) override final;
virtual void Union(int p, int q) override final;

private:
int Root(int p);

std::vector<int> m_connectedTo;
std::vector<int> m_sizeOfTree;

};

} // namespace alg