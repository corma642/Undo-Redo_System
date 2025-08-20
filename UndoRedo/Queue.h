#pragma once

#include "Vector.h"

template<typename T>
class Queue
{
public:
	Queue() :data(Vector<T>()), front(0), back(0), size(0) {}

	void Push(const T& value)
	{
		if (IsFull())
		{
			// 크기 증설
			int NewSize = std::max(1, size * 2);
			data.Reserve(NewSize);

			front = 0;
			back = size;
		}

		data[back++] = value;
		data.Resize(data.Size() + 1);
		++size;
	}

	void Pop()
	{
		front = (front + 1) % data.Size();
		--size;
	}

	T& Front()
	{
		return data[front];
	}

	int Size() const { return size; }

	bool Empty() const { return size <= 0; }

private:
	bool IsFull() const { return data.Size() == size; }

private:
	Vector<T> data;

	int front = 0;
	int back = 0;
	int size = 0;
};