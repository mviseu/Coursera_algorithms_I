#pragma once
#include <memory>

template <typename T>
struct Node {
Node(const T& itm, std::shared_ptr<Node> pr, std::shared_ptr<Node> nt) : item(itm), prev(pr), next(nt) {}

T item = T();
std::shared_ptr<Node> prev;
std::shared_ptr<Node> next;
};

template <typename T>
class BidirectionalLinkedList {
public:
BidirectionalLinkedList() = default;
bool IsEmpty() const;
int Size() const;
void PushFront(const T& itm);
void PushBack(const T& itm);
void PopFront();
void PopBack();

private:
void PopWhenEmpty();

int m_size{0};
std::shared_ptr<Node<T>> m_front;
std::shared_ptr<Node<T>> m_back;
};

template <typename T>
bool BidirectionalLinkedList<T>::IsEmpty() const {
	return m_size == 0;
}

template <typename T>
int BidirectionalLinkedList<T>::Size() const {
	return m_size;
}

template <typename T>
void BidirectionalLinkedList<T>::PushFront(const T& itm) {
	auto old_front = m_front;
	m_front = std::make_shared<Node<T>>(itm, nullptr, old_front);
	if(IsEmpty()) {
		m_back = m_front;
	} else {
		old_front->prev = m_front;
	}
	++m_size;
}

template <typename T>
void BidirectionalLinkedList<T>::PushBack(const T& itm) {
	auto old_back = m_back;
	m_back = std::make_shared<Node<T>>(itm, old_back, nullptr);
	if(IsEmpty()) {
		m_front = m_back;
	} else {
		old_back->next = m_back;
	}
	++m_size;
}

template <typename T>
void BidirectionalLinkedList<T>::PopFront() {
	PopWhenEmpty();
	--m_size;
	m_front = m_front->next;
	if(IsEmpty()) {
		m_back = nullptr;
	} else {
		m_front->prev = nullptr;
	}
}

template <typename T>
void BidirectionalLinkedList<T>::PopBack() {
	PopWhenEmpty();
	--m_size;
	m_back = m_back->prev;
	if(IsEmpty()) {
		m_front = nullptr;
	} else {
		m_back->next = nullptr;
	}
}

template <typename T>
void BidirectionalLinkedList<T>::PopWhenEmpty() {
	if(IsEmpty()) {
		throw std::runtime_error("Cannot pop element if list is empty");
	}
}

