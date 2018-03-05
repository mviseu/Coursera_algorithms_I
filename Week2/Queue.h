#pragma once

template <typename T> 
class Queue {
public:
	virtual void Enqueue(const T&) = 0;
	virtual void Dequeue() = 0;
	virtual bool IsEmpty() const = 0;
	virtual bool IsFull() const = 0;
	/*
	virtual T First() const = 0;
	virtual T Last() const = 0;
	virtual void Reinitialize() = 0;
	*/
	virtual ~Queue() = default;
};