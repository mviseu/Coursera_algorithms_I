#pragma once
#include <vector>

namespace alg {

class QuickFind {
public:
QuickFind(int n);
bool Connected(int p, int q) const;
void Union(int p, int q);

private:
std::vector<int> m_connectedTo;

};

} // namespace alg