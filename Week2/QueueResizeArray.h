#pragma once
#include "Queue.h"

template <typename T> 
class QueueResizeArray : public Queue<T> {
public:
	QueueResizeArray() = default;
	QueueResizeArray(const QueueResizeArray&);
	QueueResizeArray(QueueResizeArray&&);
	QueueResizeArray &operator=(const QueueResizeArray&);
	QueueResizeArray &operator=(QueueResizeArray&&);


	void Enqueue(const T&) override;
	void Dequeue() override;
	bool IsEmpty() const override;
	bool IsFull() const override;
	bool IsLastEnd() const;
	T First() const override;
	T Last() const override;
	void Reinitialize() override;

private:
	bool IsQuarterFull() const;

	int m_capacity{0};
	int m_first{0}; //1 based
	int m_last{0}; // 1 based
	T * m_arr = nullptr;
};

template <typename T>
bool QueueResizeArray<T>::IsEmpty() const {
	return m_first == m_last;
}

template <typename T>
bool QueueResizeArray<T>::IsFull() const {
	return m_last - m_first == m_capacity;
}

template <typename T>
bool QueueResizeArray<T>::IsLastEnd() const {
	return m_last == m_capacity + 1;
}


template <typename T>
bool QueueResizeArray<T>::IsQuarterFull() const {
	return m_last - m_first = 0.25 * m_capacity;
}

/*

template <typename T>
void QueueResizeArray<T>::Dequeue() {
	assert(!IsEmpty());
	if(IsQuarterFull()) {
		m_capacity = m_capacity / 2;
		auto new_arr = new T[m_capacity]();
		for(auto i = m_first, j = 0; i < m_last; ++i, ++j) {
			new_arr[j] = m_arr[m_first - 1];
		}
		delete [] m_arr;
		m_arr = new_arr;
		new_arr = nullptr;
		//m_first = 1;
		//m_last = m_first + 1;
	} else {
		++m_first;
	}
}
*/

template <typename T>
void QueueResizeArray<T>::Enqueue(const T& elem) {
	auto new_first{1};
	if(IsFull()) {
		if(m_capacity) {
			m_capacity = 2 * m_capacity;
		} else {
			m_capacity = 1;
		}
		auto new_arr = new T[m_capacity]();
		for(auto i = 0; i < m_last - m_first; ++i) {
			new_arr[i] = m_arr[i + m_first - 1];
		}
		delete [] m_arr;
		m_arr = new_arr;
		new_arr = nullptr;
	} else {
		if(IsLastEnd()) {
			for(auto i = 0; i < m_last - m_first; ++i) {
				m_arr[i] = m_arr[i + m_first - 1];
			}
		} else {
			new_first = m_first;
		}
	}

	m_arr[m_last - m_first + new_first - 1] = elem;
	m_last = m_last - m_first + 1 + new_first;
	m_first = new_first;
}