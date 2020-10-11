#pragma once
#pragma once


// Signature must be retained. Implementation must be added.

#ifndef SORT_H
#define SORT_H

#include "Exceptions.h"
#include "ResizableArray.h"
#include "Comparator.h"

template <typename T>
class Sorter
{
private:
	// additional member functions (methods) and variables (fields) may be added


public:
	static void sort(ResizableArray<T>& array, const Comparator<T>& comparator)
	{

		Quicksort(array, (long long int) 0, (long long int)(array.getSize() - 1), comparator);
		/*T temp;
		for (int i = 0; i < array.getSize; i++)
		{
			j = i;
			while (j > 0 && comparator.compare(j, array[j - 1]) < 0)
			{
				temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;
				--j;

			}
		}*/
	}
	static void swap(ResizableArray<T>& array, long long int index, long long  int index2);
	static void Quicksort(ResizableArray<T>& array, long long int left, long long int right, const Comparator<T>& comparator);


};
template<typename T>
void Sorter<T>::swap(ResizableArray<T>& array, long long int index, long long int index2)
{
	T temp = array.get(index);
	array.replaceAt(array.get(index2), index);
	array.replaceAt(temp, index2);
}

template<typename T>
void Sorter<T>::Quicksort(ResizableArray<T>& array, long long int left, long long int right, const Comparator<T>& comparator)
{
	if (left < right)
	{
		long long int pivot = (left + right) / 2;
		long long i = left - 1;
		long long  j = right + 1;
		do
		{
			do
			{
				i = i + 1;
			} while (i < (long long int)array.getSize() && comparator.compare(array[i], array[pivot]) <= 0);
			do
			{
				j = j - 1;
			} while (j >= i && comparator.compare(array[j], array[pivot]) >= 0);
			if (i < j)
			{
				swap(array, i, j);
			}
		} while (i < j);
		if (i < pivot)
		{
			j = i;
		}
		swap(array, j, pivot);
		Quicksort(array, left, j - 1, comparator);
		Quicksort(array, j + 1, right, comparator);
	}
}
#endif