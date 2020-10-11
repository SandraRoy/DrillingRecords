#pragma once
#pragma once

#ifndef RESIZABLE_ARRAY_H
#define RESIZABLE_ARRAY_H

#include "Exceptions.h"

const unsigned long DEFAULT_ARRAY_CAPACITY = 10;        // capacity used in no arg constructor

template <typename T>
class ResizableArray {
private:
	unsigned long capacity = DEFAULT_ARRAY_CAPACITY;    // maximum capacity, in items
	unsigned long size = 0;                             // actual number of items currently in array
	T* data = NULL;                                     // pointer to array of any type
	void doubleCapacity();                              // method to double array capacity
	void halveCapacity();                               // method to halve array capacity
public:
	ResizableArray();                                   // constructs array with default capacity
	ResizableArray(unsigned long capacity);             // constructs array with specified capacity
	virtual ~ResizableArray();                          // frees array space as object is deleted
	void add(T item);                                   // adds item, increments size, doubles capacity as necessary
	void addAt(T item, unsigned long index);            // adds item at index, shifts following, doubles capacity as necessary
	void replaceAt(T item, unsigned long index);        // replaces item at index, otherwise unchanged
	void removeAt(unsigned long index);                 // removes item at index, shifts following back
	T get(unsigned long index) const;                   // returns (copy of) item at index
	unsigned long getSize() const;                      // returns number of items currently in array
	unsigned long getCapacity() const;                  // returns the current capacity of the array
	T operator[](unsigned long index) const;            // returns (copy of) item at index
	void clear();                                       // removes all items from array, resets to default capacity, set size to 0
};

// Add your implementation below this line. Do not add or modify anything above this line.
template<typename T>
inline void ResizableArray<T>::doubleCapacity()
{
	capacity = capacity * 2;
	T* largerArray = new T[capacity];
	for (unsigned int i = 0; i < size; i++)
	{
		largerArray[i] = data[i];// copies values from data array into the new array with double capacity
	}
	delete[] data;
	data = largerArray;
}
template<typename T>
inline void ResizableArray<T>::halveCapacity()
{
	capacity = capacity / 2;
	T* smallerArray = new T[capacity];
	for (unsigned int i = 0; i < size; i++)
	{
		smallerArray[i] = data[i];
	}
	delete[] data;
	data = smallerArray;
	smallerArray = NULL;
}

template<typename T>
inline ResizableArray<T>::ResizableArray()
{
	data = new T[capacity];
}
template<typename T>
inline ResizableArray<T>::ResizableArray(unsigned long capacity)
{
	this->capacity = capacity;
	data = new T[capacity];
}

template<typename T>
inline ResizableArray<T>::~ResizableArray()
{
	delete[]data;
	data = NULL;
}
template<typename T>
void ResizableArray<T>::add(T item)
{
	if (size >= capacity)
	{
		doubleCapacity();
	}
	data[size] = item;
	size++;

}

template<typename T>
void ResizableArray<T>::addAt(T item, unsigned long index)
{
	if (index > size)
	{
		throw  new ExceptionIndexOutOfRange; //exception is thrown for any index out of size range
	}
	if (size >= capacity)
	{
		doubleCapacity();
	}

	for (unsigned long i = size; i > index; i--)
	{
		data[i] = data[i - 1]; //the elements after index are shifted to the right to allocate item to the given index
	}
	data[index] = item;
	size++;
}

template<typename T>
void ResizableArray<T>::replaceAt(T item, unsigned long index)
{
	if (index < size)
	{
		data[index] = item;
	}
	else
	{
		throw new ExceptionIndexOutOfRange;
	}
}
template<typename T>
void ResizableArray<T>::removeAt(unsigned long index)
{
	if (index >= size)
	{
		throw  new ExceptionIndexOutOfRange;
	}

	for (unsigned long i = index; i < size - 1; i++)
		/*  starting loop at index to be removed, elemnts are shifted to the left in order to remove the elemnt at the given index*/
	{
		data[i] = data[i + 1];
	}

	data[size - 1] = T();
	size--;

	if (size <= capacity / 2)
	{
		halveCapacity();
	}
}
template<typename T>
inline T ResizableArray<T>::get(unsigned long index) const
{
	if (index >= size)
	{
		throw new ExceptionIndexOutOfRange;
	}

	return data[index];
}

template<typename T>
inline T ResizableArray<T>::operator[](unsigned long index) const
{
	return data[index];
}

template<typename T>
inline void ResizableArray<T>::clear()
{
	delete[]data;
	capacity = DEFAULT_ARRAY_CAPACITY;
	data = new T[capacity];
	this->size = 0;
}

template<typename T>
inline unsigned long ResizableArray<T>::getSize() const
{
	return size;
}
template<typename T>
inline unsigned long ResizableArray<T>::getCapacity() const
{
	/*delete[]data;
	data = NULL;
	this.size = 0;
	this->capacity = DEFAULT_ARRAY_CAPACITY;*/
	return capacity;
}

#endif