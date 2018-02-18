#include "Percolation.h"
#include "RowColumn.h"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <utility>
#include <iostream>


namespace perc {

namespace {

int ToZeroBased(int i) {
	return i - 1;
}

int VirtualTopPos(int n) {
	return n * n;
}

int VirtualBottomPos(int n) {
	return VirtualTopPos(n) + 1;
}

RowColumn InitRowColumn(int r, int c, int n) {
	return RowColumn(ToZeroBased(r), ToZeroBased(c), n);	
}

void IfTopUnionVirtual(alg::UnionFind& uf, const RowColumn& grid) {
	if(grid.IsTopRow()) {
		uf.Union(grid.Position1D(), VirtualTopPos(grid.GetMax()));
	}
}

void IfBottomUnionVirtual(alg::UnionFind& uf, const RowColumn& grid) {
	if(grid.IsBottomRow()) {
		uf.Union(grid.Position1D(), VirtualBottomPos(grid.GetMax()));
	}
}

void IfUnionVirtual(alg::UnionFind& uf, const RowColumn& grid) {
	IfTopUnionVirtual(uf, grid);
	IfBottomUnionVirtual(uf, grid);
}

void IfOpenUnion(const std::vector<bool>& openSites, alg::UnionFind& uf, int posOpenBase, int posDest) {
	if(openSites[posDest]) {
		uf.Union(posOpenBase, posDest);
	}
}

void IfOpenUnionUp(const std::vector<bool>& openSites, alg::UnionFind& uf, const RowColumn& grid) {
	if(!grid.IsTopRow()) {
		const auto topGrid = RowColumn(grid.GetRow() - 1, grid.GetColumn(), grid.GetMax());
		IfOpenUnion(openSites, uf, grid.Position1D(), topGrid.Position1D());
	}
}

void IfOpenUnionDown(const std::vector<bool>& openSites, alg::UnionFind& uf, const RowColumn& grid) {
	if(!grid.IsBottomRow()) {
		const auto botGrid = RowColumn(grid.GetRow() + 1, grid.GetColumn(), grid.GetMax());
		IfOpenUnion(openSites, uf, grid.Position1D(), botGrid.Position1D());	
	}
}

void IfOpenUnionLeft(const std::vector<bool>& openSites, alg::UnionFind& uf, const RowColumn& grid) {
	if(!grid.IsLeftColumn()) {
		const auto leftGrid = RowColumn(grid.GetRow(), grid.GetColumn() - 1, grid.GetMax());
		IfOpenUnion(openSites, uf, grid.Position1D(), leftGrid.Position1D());
	}
}

void IfOpenUnionRight(const std::vector<bool>& openSites, alg::UnionFind& uf, const RowColumn& grid) {
	if(!grid.IsRightColumn()) {
		const auto rightGrid = RowColumn(grid.GetRow(), grid.GetColumn() + 1, grid.GetMax());
		IfOpenUnion(openSites, uf, grid.Position1D(), rightGrid.Position1D());
	}	
}

void IfUnionSides(const std::vector<bool>& openSites, alg::UnionFind& uf, const RowColumn& grid) {
	IfOpenUnionUp(openSites, uf, grid);
	IfOpenUnionDown(openSites, uf, grid);
	IfOpenUnionLeft(openSites, uf, grid);
	IfOpenUnionRight(openSites, uf, grid);
}

} // namespace


Percolation::Percolation(int n)  {
	if(n <=0) {
		throw std::out_of_range("n provided to construct percolation grid must be greater than zero");
	}
	std::fill_n(std::back_inserter(m_openSites), n*n, false);
	m_uf = std::make_shared<alg::WQUPC>(alg::WQUPC(n*n + 2));
}

bool Percolation::IsOpen(int r, int c) const {
	const auto grid = InitRowColumn(r, c, GetN());
	return m_openSites[grid.Position1D()];
}

void Percolation::Open(int r, int c) {
	if(!IsOpen(r, c)) {
		const auto grid = InitRowColumn(r, c, GetN());
		m_openSites[grid.Position1D()] = true;
		IfUnionVirtual(*m_uf, grid);
		IfUnionSides(m_openSites, *m_uf, grid);
	}
}

int Percolation::NrOpenSites() const {
	return std::count(m_openSites.cbegin(), m_openSites.cend(), true);
}

int Percolation::GetN() const {
	return std::sqrt(m_openSites.size());
}

bool Percolation::IsFull(int r, int c) const {
	const auto grid = InitRowColumn(r, c, GetN()); 
	return m_uf->Connected(grid.Position1D(), VirtualTopPos(GetN()));
}

bool Percolation::Percolates() const {
	return m_uf->Connected(VirtualBottomPos(GetN()), VirtualTopPos(GetN()));
}

} // namespace perc