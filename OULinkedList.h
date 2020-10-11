#pragma once
#pragma once

#ifndef OU_LINKED_LIST
#define OU_LINKED_LIST

#include "OULink.h"
#include "Comparator.h"
#include "OULinkedListEnumerator.h"

// OULinkedList stands for Ordered, Unique Linked List. It is a linked list that is always maintained in
// order (based on the comparator provided to it when the list is created) and that only contains unique
// items (that is, duplicates are not allowed)
template <typename T>
class OULinkedList {
	//template <typename T>
	//friend class OULinkedListEnumerator;
private:
	Comparator<T>* comparator = NULL;               // used to determine list order and item equality
	unsigned long size = 0;                         // actual number of items currently in list
	OULink<T>* first = NULL;                        // pointer to first link in list
	OULink<T>* last = NULL;                         // pointer to last link in list
public:
	OULinkedList(Comparator<T>* comparator);        // creates empty linked list with comparator
	virtual ~OULinkedList();                        // deletes all links and their data items

	// if an equivalent item is not already present, insert item in order and return true
	// if an equivalent item is already present, leave list unchanged and return false
	bool insert(T item);

	// if item is greater than item at last, append item at end and return true
	// if item is less than or equal to item at last, leave list unchanged and return false
	bool append(T item);

	// if an equivalent item is already present, replace item and return true
	// if an equivalent item is not already present, leave list unchanged and return false
	bool replace(T item);

	// if an equivalent item is already present, remove item and return true
	// if an equivalent item is not already present, leave list unchanged and return false
	bool remove(T item);

	// if any items are present, return a copy of the first item
	// if no items are present, throw new ExceptionLinkedListAccess
	T getFirst() const;

	// if any items are present, return a copy of the first item, remove it from list
	// if no items are present, throw new ExceptionLinkedListAccess
	T pullFirst();

	// if any items are present, remove the first item and return true
	// if no items are present, leave list unchanged and return false
	bool removeFirst();

	// if an equivalent item is present, return true
	// if an equivalent item is not present, false
	bool contains(T item) const;

	// if an equivalent item is present, return a copy of that item
	// if an equivalent item is not present, throw a new ExceptionLinkedListAccess
	T find(T item) const;

	void clear();                                     // deletes all links in the list, resets size to 0

	unsigned long getSize() const;                    // returns the current number of items in the list

	OULinkedListEnumerator<T> enumerator() const;     // create an enumerator for this linked list
};

// Add your implementation below this line. Do not add or modify anything above this line.


#endif // !OU_LINKED_LIST

template<typename T>
inline OULinkedList<T>::OULinkedList(Comparator<T>* comparator)
{
	this->comparator = comparator;
}


template<typename T>
inline OULinkedList<T>::~OULinkedList()
{
	OULink<	T>* item = first;
	while (item != nullptr)
	{
		OULink<T>* newItem = item->next;
		delete item;

		item = newItem;
	}
	first = NULL;
}


template<typename T>
inline bool OULinkedList<T>::insert(T item)
{
	//OULink<T>* newItem = new OULink<T>(item);
	if (first == nullptr)
	{
		OULink<T>* newItem = new OULink<T>(item);
		first = newItem;
		last = newItem;
		size++;
		return true;
	}
	else
	{
		OULink<T>* p = nullptr;
		OULink<T>* c = first;
		OULink<T>* newItem = new OULink<T>(item);
		while (c != nullptr && comparator->compare(c->data, newItem->data) < 0)//traverses the list till it reaches the end or current variable is greater than item to be inserted
		{
			p = c;
			c = c->next;
		}
		if (c != nullptr && comparator->compare(c->data, newItem->data) == 0)
		{
			return false;
		}
		if (p == nullptr)
		{
			newItem->next = first;
			first = newItem;
			size++;
			return true;

		}
		else if (c == nullptr)
		{

			last->next = newItem;
			last = newItem;
			size++;
			return true;
		}

		else
		{
			p->next = newItem;
			newItem->next = c;
			size++;
			return true;
		}
	}
	return false;
}

template<typename T>
inline bool OULinkedList<T>::append(T item)
{
	OULink<T>* newItem = new OULink<T>(item);
	if (first == nullptr)
	{

		first = newItem;
		last = newItem;
		size++;
		return true;
	}
	else if (comparator->compare(last->data, newItem->data) < 0)
	{

		last->next = newItem;
		last = newItem;
		size++;
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
inline bool OULinkedList<T>::replace(T item)// if an equivalent item is already present, replace item and return true
	// if an equivalent item is not already present, leave list unchanged and return false
{
	OULink<T>* current = first;
	OULink<T>* newItem = new OULink<T>(item);
	bool value = false;
	while (current != nullptr && comparator->compare(current->data, newItem->data) != 0)
	{

		current = current->next;
	}
	if (current != nullptr && comparator->compare(current->data, newItem->data) == 0)
	{
		value = true;
		current->data = newItem->data;
	}
	return value;

}


// if an equivalent item is already present, remove item and return true
// if an equivalent item is not already present, leave list unchanged and return false
template<typename T>
inline bool OULinkedList<T>::remove(T item)
{

	if (first == nullptr)
	{

		return false;
	}
	else
	{
		OULink<T>* p = nullptr;
		OULink<T>* c = first;
		OULink<T>* newItem = new OULink<T>(item);
		while (c != nullptr && comparator->compare(c->data, newItem->data) != 0)
		{
			p = c;
			c = c->next;
		}
		if (p == nullptr)
		{
			first = c->next;
			c->next = nullptr;
			delete c;
			size--;
			return true;
		}
		else if (c == nullptr)
		{
			//p->next = nullptr;
			//delete c;
			//size--;
			return false;
		}
		else
		{
			p->next = c->next;
			c->next = nullptr;
			delete c;
			size--;
			return true;
		}
		return false;

	}
}

// if any items are present, return a copy of the first item
// if no items are present, throw new ExceptionLinkedListAccess
template<typename T>
inline T OULinkedList<T>::getFirst() const

{
	if (first == nullptr)
	{
		throw new ExceptionLinkedListAccess;
	}
	else
	{
		return first;
	}

}

template<typename T>
inline T OULinkedList<T>::pullFirst()
{
	if (first == nullptr)
	{
		throw new ExceptionLinkedListAccess;
	}
	else
	{
		OULink<T>* current = first;
		OULink<T>* copy = current;
		first = current->next;
		current->next = nullptr;
		delete current;
		return copy->data;
	}

}

template<typename T>
inline bool OULinkedList<T>::removeFirst()
{
	if (first == nullptr)
	{
		return false;
	}
	else
	{
		OULink<T>* current = first;

		first = current->next;
		current->next = nullptr;
		delete current;
		return true;
	}
}

// if an equivalent item is present, return true
	// if an equivalent item is not present, false
template<typename T>
inline bool OULinkedList<T>::contains(T item) const
{
	//try
	//	find()
	//	return true
	//catch (
	//	retun false


	if (first == nullptr)
	{
		return false;
	}
	OULink<T>* newItem = new OULink<T>(item);
	//OULink<T>* previous = null;
	OULink<T>* current = first;
	while (current != nullptr && comparator->compare(newItem->data, current->data) != 0)
	{
		//previous = current;
		current = current->next;
	}
	if (current != nullptr && comparator->compare(newItem->data, current->data) == 0)
	{
		return true;

	}
	else
	{
		return false;
	}


}


template<typename T>
inline unsigned long OULinkedList<T>::getSize() const
{
	if (first == nullptr)
	{
		return 0;
	}
	OULink<T>* current = first;
	int size = 0;
	while (current != nullptr)
	{
		current = current->next;
		size++;
	}
	return size;

}

// if an equivalent item is present, return a copy of that item
// if an equivalent item is not present, throw a new ExceptionLinkedListAccess
template<typename T>
inline T OULinkedList<T>::find(T item) const
{
	if (first == nullptr)
	{
		throw new ExceptionLinkedListAccess;
	}
	OULink<T>* current = first;
	OULink<T>* newItem = new OULink<T>(item);
	while (current != nullptr && comparator->compare(newItem->data, current->data) != 0)
	{
		current = current->next;
	}
	if (current == nullptr)
	{
		throw new ExceptionLinkedListAccess;
	}
	if (comparator->compare(newItem->data, current->data) == 0)
	{
		return current->data;
	}
	throw new ExceptionLinkedListAccess;
}

template<typename T>
inline void OULinkedList<T>::clear()
{
	delete first;
}

template<typename T>
inline OULinkedListEnumerator<T> OULinkedList<T>::enumerator() const
{
	return OULinkedListEnumerator<T>(first);
}


