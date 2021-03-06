#pragma once
#include "UnionFind.h"
#include <vector>

namespace alg {

class QuickFind : public UnionFind {

public:
explicit QuickFind(int n);
virtual bool Connected(int p, int q) override final;
virtual void Union(int p, int q) override final;

private:
std::vector<int> m_connectedTo;

};

} // namespace alg