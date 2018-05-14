#pragma once
#include "BinarySearchNode.h"
#include <iterator>
#include <cstddef>
#include <type_traits>

template <typename Value, typename UnqualifiedValue = std::remove_cv_t<Value>>
class BinarySearchTreeIt {
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = UnqualifiedValue;
	using difference_type = std::ptrdiff_t;
	using pointer = Value*;
	using reference = Value&;
	using Key = decltype(value_type::first);
	using T = decltype(value_type::second);
	explicit BinarySearchTreeIt(const std::shared_ptr<Node<Key, T>>& it, const std::shared_ptr<Node<Key, T>>& bfrnt, const std::shared_ptr<Node<Key, T>>& aftbck) 
	: iterator(it), beforeFront(bfrnt), afterBack(aftbck) {}

private:
	std::shared_ptr<Node<Key, T>> iterator;
	std::shared_ptr<Node<Key, T>> beforeFront;
	std::shared_ptr<Node<Key, T>> afterBack;
};