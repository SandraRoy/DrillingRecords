#pragma once
#pragma once


// Signature must be retained. Implementation must be added.

#ifndef SEARCH_H
#define SEARCH_H

#include "Exceptions.h"
#include "ResizableArray.h"
#include "Comparator.h" 

// returns FIRST array location matching the given item (based on the comparator) 
// if not found, returns -(location to insert + 1)
template <typename T>
long long binarySearch(const T& item, const ResizableArray<T>& array, const Comparator<T>& comparator)
{
	long mid = 0;
	long high = array.getSize() - 1;
	long low = 0;
	bool found = false;
	while (high >= low && found == false)
	{
		mid = (high + low) / 2;
		if (comparator.compare(item, array[mid]) > 0)
		{
			low = mid + 1;
		}
		else if (comparator.compare(item, array[mid]) < 0)
		{
			high = mid - 1;
		}
		else
		{
			found = true;
		}
	}

	if (found == false)
	{
		return (mid + 1) * -1;
	}
	else
	{

		while (comparator.compare(array[mid], array[mid - 1]) == 0 && mid != 0)
		{

			mid = mid - 1;
		}
		return mid;
	}
}


// implementation goes here


#endif