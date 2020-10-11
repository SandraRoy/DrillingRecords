#pragma once
#pragma once

#ifndef OU_LINK_H
#define OU_LINK_H

template <typename T>
class OULink {
	template <typename A>
	friend class OULinkedList;
	template <typename A >
	friend class OULinkedListEnumerator;
private:
	T data{};                  // data item of any type
	OULink* next = NULL;       // pointer to next link
public:
	OULink(T item);
	virtual ~OULink();
};

// Add your implementation below this line. Do not add or modify anything above this line.


#endif // !OU_LINK

template<typename T>
inline OULink<T>::OULink(T item)
{
	data = item;
}



template<typename T>
inline OULink<T>::~OULink()
{
	next = NULL;
	delete next;
}
