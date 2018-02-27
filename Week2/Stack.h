#pragma once

template <typename T>
class Stack {
public:
	virtual void Reinitialize() = 0;
	virtual bool IsEmpty() const = 0;
	virtual bool IsFull() const = 0;
	virtual void Pop() = 0;
	virtual void Push(const T&) = 0;
	virtual T Top() const = 0;
	virtual ~Stack() = default;
};