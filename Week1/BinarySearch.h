#pragma once
#include <utility>
#include <vector>

std::pair<bool, std::vector<int>::const_iterator> BinarySearch(const std::vector<int>& sortedVec, int key);