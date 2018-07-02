#pragma once
#include <memory>

const decltype(nullptr) nullopt = nullptr;

template <typename T>
class Optional {
public:
	Optional(const decltype(nullptr)& null) : opt(null) {}
	Optional(const T& val) : opt(std::make_unique<T>(val)) {}
	Optional& operator=(const T& rhs) {
		opt = std::make_unique<T>(rhs);
		return *this;
	}
	Optional& operator=(const decltype(nullptr)& null) {
		opt = null;
		return *this;
	}
	explicit operator bool() const {return opt != nullptr;}
	T& operator*() const {
		return *opt;
	}
private:
	std::unique_ptr<T> opt;
};
