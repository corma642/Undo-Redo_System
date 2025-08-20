#pragma once

#include "Vector.h"

template<typename T>
class Stack
{
public:
	Stack() :data(Vector<T>()) {}

	void Push(const T& value)
	{
		data.Push_back(value);
	}

	void Pop()
	{
		data.Pop_back();
	}

	const Vector<T>& GetData() const { return data; }

	T& Top() const { return data.Back(); }

	int Size() const { return data.Size(); }

	bool Empty() const { return Size() <= 0; }

private:
	Vector<T> data;
};