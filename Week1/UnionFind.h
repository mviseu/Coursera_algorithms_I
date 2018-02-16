#pragma once

namespace alg {

class UnionFind {

public:
UnionFind() = default;
virtual ~UnionFind() noexcept = default;

virtual bool Connected(int p, int q) = 0;
virtual void Union(int p, int q) = 0;
};


}