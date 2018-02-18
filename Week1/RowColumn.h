#pragma once

namespace perc {

class RowColumn {
public:
	// Receives 1 based but all calculations will be zero based
	RowColumn(int r, int c, int m);
	int Position1D() const;

	bool IsLeftColumn() const;
	bool IsRightColumn() const;
	bool IsTopRow() const;
	bool IsBottomRow() const;
	
	int GetMax() const;
	int GetRow() const;
	int GetColumn() const;
private:
	void CheckRange() const;
	int m_row = 0;
	int m_column = 0;
	int m_max = 0;
};


} // namespace