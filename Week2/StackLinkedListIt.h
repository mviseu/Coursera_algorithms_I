#include "StackLinkedList.h"
#include <assert.h>

template <typename T> class StackLinkedListIt;
template <typename T> bool operator==(const StackLinkedListIt<T>& lhs, const StackLinkedListIt<T>& rhs);
template <typename T> bool operator!=(const StackLinkedListIt<T>& lhs, const StackLinkedListIt<T>& rhs);


template<typename T>
class StackLinkedListIt {

friend bool operator== <T>(const StackLinkedListIt<T>& lhs, const StackLinkedListIt<T>& rhs);
friend bool operator!= <T>(const StackLinkedListIt<T>& lhs, const StackLinkedListIt<T>& rhs);
public:
StackLinkedListIt() = default;
T& operator*() const;
T* operator->() const;
StackLinkedListIt& operator++();
StackLinkedListIt operator++(int);


private:
Node<T>* ptr = nullptr;
};

template<typename T>
bool operator==(const StackLinkedListIt<T>& lhs, const StackLinkedListIt<T>& rhs) {
	return lhs.ptr == rhs.ptr;
}

template <typename T>
bool operator!=(const StackLinkedListIt<T>& lhs, const StackLinkedListIt<T>& rhs) {
	return !(lhs == rhs);
}

template<typename T>
T& StackLinkedListIt<T>::operator*() const {
	assert(!nullptr);
	return ptr->item;
}

template<typename T>
T* StackLinkedListIt<T>::operator->() const {
	return & this->operator*();
}

template <typename T>
StackLinkedListIt<T>& StackLinkedListIt<T>::operator++() {
	assert(!ptr);
	ptr = ptr->next;
	return *this;
}

template <typename T>
StackLinkedListIt<T> StackLinkedListIt<T>::operator++(int) {
	auto curr = *this;
	++*this;
	return curr;
}
