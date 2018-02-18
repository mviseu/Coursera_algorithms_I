#include "RowColumn.h"
#include <stdexcept>
#include <string>
#include <iostream>

namespace perc {

namespace {

int MinLimit() {
	return 0;
}

int MaxLimit(int max) {
	return max - 1;
}

void CheckIndex(int index, int max) {
	if(index < MinLimit() || index > MaxLimit(max)) {
		throw std::out_of_range("index is out of range");
	}		
}

} // namespace

RowColumn::RowColumn(int r, int c, int m) : m_row(r), m_column(c), m_max(m) {
	CheckRange();
}

int RowColumn::Position1D() const {
	return m_row * m_max + m_column;
}

bool RowColumn::IsLeftColumn() const {
	return m_column == MinLimit();
}

bool RowColumn::IsRightColumn() const {
	return m_column == MaxLimit(m_max);
}

bool RowColumn::IsTopRow() const {
	return m_row == MinLimit();
}

bool RowColumn::IsBottomRow() const {
	return m_row == MaxLimit(m_max);
}

int RowColumn::GetMax() const {
	return m_max;
}

int RowColumn::GetRow() const {
	return m_row;
}

int RowColumn::GetColumn() const {
	return m_column;
}

void RowColumn::CheckRange() const {
	CheckIndex(m_row, m_max);
	CheckIndex(m_column, m_max);
}

} // namespace perc