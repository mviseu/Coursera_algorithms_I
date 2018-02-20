#pragma once

#include <iostream>

namespace perc {

class PercolationStats {
public:
PercolationStats(int n, int trials);

double Mean() const;
double StdDev() const;
double ConfidenceLo() const;
double ConfidenceHi() const;

std::ostream& PrintStats(std::ostream&os) const; 

private:
double ConfidenceTerm() const;

double m_mean = {0.0};
double m_stdDev = {0.0};
int m_trials = {0};
};


} // namespace perc