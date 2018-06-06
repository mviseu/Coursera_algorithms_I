#pragma once

template<typename Key>
struct Range {
	Range(const Key& low, const Key& high) : lo(low), hi(high) {}
	Key lo;
	Key hi;
};

template<typename Key>
bool IsKeyInRange(const Key& key, const Range<Key>& rg) {
	return (key >= rg.lo) && (key <= rg.hi);
}


template<typename Key>
bool IsKeyGreaterLow(const Key& key, const Range<Key>& rg) {
	return key > rg.lo;
}


template<typename Key>
bool IsKeyLessHigh(const Key& key, const Range<Key>& rg) {
	return key < rg.hi;
}