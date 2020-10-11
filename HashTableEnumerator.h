#pragma once
#pragma once
#ifndef HASH_TABLE_ENUMERATOR
#define HASH_TABLE_ENUMERATOR

#include "Enumerator.h"
#include "Exceptions.h"
#include "HashTable.h"

template <typename T>
class HashTableEnumerator : public Enumerator<T>
{
private:
	unsigned long bucket = 0;
	OULinkedListEnumerator<T>* chainEnumerator = NULL;
	HashTable<T>* hashTable;
public:
	HashTableEnumerator(HashTable<T>* hashTable);
	virtual ~HashTableEnumerator();
	bool hasNext() const;
	T next();              // throws ExceptionEnumerationBeyondEnd if no next item is available
	T peek() const;        // throws ExceptionEnumerationBeyondEnd if no next item is available
};

// Add your implementation below this line.

// !HASH_TABLE_ENUMERATOR

template<typename T>
inline HashTableEnumerator<T>::HashTableEnumerator(HashTable<T>* hashTable)
{
	if (hashTable->getSize() == 0)
	{
		throw new ExceptionHashTableAccess;
	}
	this->hashTable = hashTable;
	while (bucket < hashTable->getBaseCapacity() && hashTable->table[bucket]->getSize() == 0)
	{
		bucket++;
	}
	chainEnumerator = new OULinkedListEnumerator<T>(hashTable->table[bucket]->enumerator());
}

template<typename T>
inline HashTableEnumerator<T>::~HashTableEnumerator()
{
	//delete chainEnumerator;
}

template<typename T>
inline bool HashTableEnumerator<T>::hasNext() const
{
	unsigned long temp = bucket;
	if (chainEnumerator->hasNext())
	{
		return true;
	}
	else
	{
		temp++;
		while (temp < hashTable->getBaseCapacity() && hashTable->table[temp]->getSize() == 0)
		{
			temp++;
		}
		if (temp < hashTable->getBaseCapacity())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}

template<typename T>
inline T HashTableEnumerator<T>::next()
{
	if (chainEnumerator->hasNext())
	{
		return chainEnumerator->next();
	}
	else
	{
		bucket++;
		while (bucket < hashTable->getBaseCapacity() - 1 && hashTable->table[bucket]->getSize() == 0)
		{
			bucket++;
		}
		if (bucket < hashTable->getBaseCapacity())
		{
			chainEnumerator = new OULinkedListEnumerator<T>(hashTable->table[bucket]->enumerator());
			return chainEnumerator->next();
			//return (hashTable->table[bucket]->enumerator()).next();
		}
		else
		{
			throw new ExceptionEnumerationBeyondEnd;
		}

	}
}

template<typename T>
inline T HashTableEnumerator<T>::peek() const
{
	unsigned long temp = bucket;
	if (chainEnumerator->hasNext())
	{
		return chainEnumerator->peek();
	}
	else
	{
		temp++;
		while (temp < hashTable->getBaseCapacity() - 1 && hashTable->table[temp]->getSize() == 0)
		{
			temp++;
		}
		if (temp < hashTable->getBaseCapacity())
		{
			return (hashTable->table[temp]->enumerator()).peek();

		}

		throw new ExceptionEnumerationBeyondEnd;


	}
	if (chainEnumerator->hasNext())
	{
		return chainEnumerator->peek();
	}
	else
	{
		throw new ExceptionEnumerationBeyondEnd;
	}
}

#endif 