#include "PercolationStats.h"
#include "Percolation.h"
#include "Threshold.h"
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>
#include <cmath>
#include <stdexcept>
#include <iomanip>


namespace perc {

namespace {

double MeanCalc(const std::vector<double>& thresholds, int trials) {
	return std::accumulate(thresholds.cbegin(), thresholds.cend(), 0.0) / trials;
}

double StdDevCalc(const std::vector<double>& thresholds, double mean, int trials) {
	std::vector<double> diff(trials);
	std::transform(thresholds.cbegin(), thresholds.cend(), diff.begin(), [&mean](double d){return d - mean;});
	auto stdDevSquare = std::inner_product(diff.cbegin(), diff.cend(), diff.cbegin(), 0.0);
	return std::sqrt(stdDevSquare / (trials - 1));
}

} // namespace

PercolationStats::PercolationStats(int n, int trials) : m_trials(trials) {
	if(trials <= 0 ||  n <= 0) {
		throw std::out_of_range("number of trials and number of sites must be positive");
	}
	m_trials = trials;
	std::vector<double> thresholds(trials);
	std::generate(thresholds.begin(), thresholds.end(), [n]() {
		auto perc = Percolation(n);
		return perc.Run().threshold;
	});
	m_mean = MeanCalc(thresholds, trials);
	m_stdDev = StdDevCalc(thresholds, m_mean, trials);
}

double PercolationStats::Mean() const {
	return m_mean;
}

double PercolationStats::StdDev() const {
	return m_stdDev;
}

double PercolationStats::ConfidenceLo() const {
	return m_mean - ConfidenceTerm();
}

double PercolationStats::ConfidenceHi() const {
	return m_mean + ConfidenceTerm();
}

double PercolationStats::ConfidenceTerm() const {
	return 1.96 * m_stdDev / std::sqrt(m_trials);
}

std::ostream& PercolationStats::PrintStats(std::ostream& os) const {
	constexpr auto pad = 30;
	os << std::left;
	os << std::setw(pad) << "mean: " << "= "  << Mean() << std::endl;
	os << std::setw(pad) << "stddev: " << "= " << StdDev() << std::endl;
	os << std::setw(pad) << "95% confidence interval: " << "= ["
	   << ConfidenceLo() << ", " << ConfidenceHi() << "]" << std::endl;
	os << std::right;
	return os;
}

} // namespace perc