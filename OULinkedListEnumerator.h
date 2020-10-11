#pragma once
#pragma once

#ifndef OU_LINKED_LIST_ENUMERATOR
#define OU_LINKED_LIST_ENUMERATOR

#include "Enumerator.h"
#include "OULink.h"

template <typename T>
class OULinkedListEnumerator : public Enumerator<T>
{
private:
	OULink<T>* current;
public:
	OULinkedListEnumerator(OULink<T>* first);
	bool hasNext() const;
	T next();			// throws ExceptionEnumerationBeyondEnd if no next item is available
	T peek() const;		// throws ExceptionEnumerationBeyondEnd if no next item is available
};

// Add your implementation below this line. Do not add or modify anything above this line.


#endif // !OU_LINKED_LIST_ENUMERATOR

template<typename T>
inline OULinkedListEnumerator<T>::OULinkedListEnumerator(OULink<T>* first)
{
	current = first;
}

template<typename T>
inline bool OULinkedListEnumerator<T>::hasNext() const
{
	if (current == nullptr)
	{
		return false;
	}

	else
	{
		return true;
	}
}

template<typename T>
inline T OULinkedListEnumerator<T>::next()
{
	if (hasNext())
	{
		OULink<T>* copy = current;
		current = current->next;
		return copy->data;
	}
	else
	{
		throw new ExceptionEnumerationBeyondEnd();
	}
}

template<typename T>
inline T OULinkedListEnumerator<T>::peek() const
{
	if (hasNext())
	{

		return current->data;
	}
	else
	{
		throw new ExceptionEnumerationBeyondEnd;
	}
}

