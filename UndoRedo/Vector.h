#pragma once

#include <iostream>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

template<typename T>
class Vector
{
public:
	Vector()
		: size(0), capacity(2)
	{
		data = new T[capacity]{};
	}

	Vector(const int NewSize)
		: data(nullptr), size(NewSize), capacity(NewSize)
	{
		data = new T[NewSize]{};
	}

	~Vector()
	{
		if (data)
		{
			delete[] data;
			data = nullptr;
		}
	}

	void Push_back(const T& value)
	{
		if (size == capacity)
		{
			int NewCapacity = capacity * 2;
			if (capacity == NewCapacity) NewCapacity++;
			Reserve(NewCapacity);
		}

		data[size++] = value;
	}

	void Pop_back()
	{
		if (size <= 0) return;
		size--;
	}

	void Reserve(const int NewCapacity)
	{
		if (capacity >= NewCapacity) return;

		capacity = NewCapacity;

		T* NewData = new T[NewCapacity]();
		memset(NewData, 0, sizeof(T) * NewCapacity);

		memcpy_s(NewData, sizeof(T) * NewCapacity, data, sizeof(T) * capacity);

		for (int i = 0; i < size; ++i)
		{
			NewData[i] = this->data[i];
		}

		if (data)
		{
			delete[] data;
			data = nullptr;
		}

		data = NewData;
	}

	void Resize(const int NewSize)
	{
		if (size >= NewSize) return;

		size = NewSize;

		if (capacity < NewSize)
		{
			capacity = NewSize;
		}
	}

	T& operator[](const int pos)
	{
		return data[pos];
	}

	const T& operator[](const int pos) const
	{
		return data[pos];
	}

	T& Back() const
	{
		if (size > 0)
		{
			return data[size - 1];
		}
	}

	T* begin() { return data; }

	T* end() { return data + size; }

	int Size() const { return size; }

	int Capacity() const { return capacity; }

	bool Empty() const { return size <= 0; }

private:
	T* data = nullptr;
	int size = 0;
	int capacity = 2;
};