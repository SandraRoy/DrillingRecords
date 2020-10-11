#pragma once
#ifndef AVL_TREE
#define AVL_TREE

#include "Comparator.h"
#include "AVLTreeEnumerator.h"

template <typename T>
class AVLTree {
	template <typename U>
	friend class AVLTreeEnumerator;
private:
	Comparator<T>* comparator = NULL;               // used to determine tree order and item equality
	unsigned long size = 0;                         // actual number of items currently in tree
	T data{};                                       // data item of any type
	bool empty = true;                              // flag to indicate whether node contains data
	int diff = 0;                                   // height of right minus height of left
	AVLTree<T>* left = NULL;                        // pointer to left subtree
	AVLTree<T>* right = NULL;                       // pointer to right subtree
	void zig();                                     // right rotation
	void zag();                                     // left rotation
	void zigzag();                                  // left rotation on left subtree, followed by right rotation
	void zagzig();                                  // right rotation on right subtree, followed by left rotation
	void rebalance();                               // check for and rebalance this node, if needed
public:
	AVLTree(Comparator<T>* comparator);             // creates empty linked tree with comparator
	virtual ~AVLTree();                             // deletes subtrees

	// if an equivalent item is not already present, insert item in order and return true
	// if an equivalent item is already present, leave tree unchanged and return false
	bool insert(const T item);

	// if an equivalent item is already present, replace item and return true
	// if an equivalent item is not already present, leave tree unchanged and return false
	bool replace(const T item);

	// if an equivalent item is already present, remove item and return true
	// if an equivalent item is not already present, leave tree unchanged and return false
	bool remove(const T item);

	// if an equivalent item is present, return true
	// if an equivalent item is not present, false
	bool contains(T item) const;

	// if an equivalent item is present, return a copy of the item
	// if an equivalent item is not present, throw a new ExceptionLinkedtreeAccess
	T find(const T item) const;

	unsigned long getSize() const;                  // returns the current number of items in the tree

	AVLTreeEnumerator<T> enumerator(AVLTreeOrder order = AVLTreeOrder::inorder) const;    // create an enumerator for this AVL tree
};

// Add your implementation below this line.
template<typename T>
inline AVLTree<T>::AVLTree(Comparator<T>* comparator)
{
	this->comparator = comparator;
}

template<typename T>
inline AVLTree<T>::~AVLTree()
{
	delete left;
	delete right;
	left = nullptr;
	right = nullptr;
}



template<typename T>
inline void AVLTree<T>::zig()   // Based on slides posted by Dr. Hougen
{
	int pDiff = diff; //parent
	int gDiff = left->diff; //right
	
		
		AVLTree<T>* leftChild = nullptr;
		
		if (left != nullptr)
		{
			leftChild = left;
			left = leftChild->left;
			leftChild->left = leftChild->right;
			leftChild->right = right;
			right = leftChild;

			T temp = this->data;
			this -> data = leftChild->data;
			leftChild->data = temp;
		}
	

		if (gDiff < 0)
		{
			diff = pDiff + 2;
			right->diff = pDiff - gDiff + 1;
		}
		else
		{
			diff = gDiff + 1;
			right->diff = pDiff + 1;
		}
	
}

template<typename T>
inline void AVLTree<T>::zag()    //Based on source posted by Dr. Hougen
{
	int pDiff = diff; //parent
	int gDiff = right->diff; //right
	
		AVLTree<T>* rightChild = nullptr;
		//AVLTree<T>* leftChild = nullptr;
		
		if (right != nullptr)
		{
			rightChild = right;
			right = rightChild->right;
			rightChild->right = rightChild->left;
			rightChild->left = left;
			left = rightChild;

			T temp = this->data;
			this->data = rightChild->data;
			rightChild->data = temp;

		}
	
	
	if (gDiff>= 0)
	{
		left->diff = pDiff-gDiff - 1;
		diff = pDiff-2;
	}
	else
	{
		diff = gDiff-1;
		left->diff = -1 + pDiff;
	}
}

template<typename T>
inline void AVLTree<T>::zigzag() //left right violation
{
	left->zag();
	zig();
}

template<typename T>
inline void AVLTree<T>::zagzig()// right left violation
{
	right->zig();
	zag();
}

template<typename T>
// Code used from Dr. Sridhar's slides
inline void AVLTree<T>::rebalance() //If diff < -1 or diff > 1, the tree is rebalanced
{
	if (diff >= -1 && diff <= 1)
	{
		return;
	}
	if (diff < 0 && left->diff <= 0)
	{
		zig();
	}
	else if (diff < 0 && left->diff>0)
	{
		zigzag();
	}
	else if (diff > 0 && right->diff < 0)
	{
		zagzig();
	}
	else if (diff > 0 && right->diff >= 0)
	{
		zag();
	}
}

template<typename T>
inline bool AVLTree<T>::insert(const T item) //Code used from Dr. Sridhar's slides
{
	if (empty)
	{
		this->data=item;
		
		empty = false;
		++size;
		return true;
	}
	
	
		if (comparator->compare(this->data,item)==0)
		{
			return false;
		}
		else if (comparator->compare(item, this->data)<0)
		{
			if (left == nullptr) // if there is no left pointer, left child is created and item is added.
			{
				left = new AVLTree<T>(comparator);
				left->data = item;
				left->size++;
				left->empty = false;
				diff--;
			}
			else
			{
				int oldLeftDiff = left->diff;
				if (left->insert(item))// recursive call
				{

					if (oldLeftDiff != left->diff && left->diff != 0)
					{
						--diff;
					}
				}
				else
				{
					return false;
				}
			}
		}
		else if (comparator->compare(item, this->data)>0)
		{
			if (right == nullptr)// If item is greater than root and there is no right pointer, right child is created and item is inserted
			{
				right = new AVLTree<T>(comparator);
				right->data = item;
				right->size++;
				right->empty = false;
				diff++;
			}
			else
			{
				int oldRightDiff = right->diff;
				if (right->insert(item))
				{

					if (oldRightDiff != right->diff && right->diff != 0)
					{
						diff++;
					}
				}
				else
				{
					return false;
				}

			}
		}
		rebalance();
		++size;
		return true;
	
}

template<typename T>
inline bool AVLTree<T>::replace(const T item) //recursive function
{
	if (!empty)
	{
		if (comparator->compare(this->data, item) == 0)
		{
			this->data = item;
			return true;
		}
		else if (left!=nullptr && comparator->compare(this->data, item) > 0 )
		{ 
			
			return left->replace(item);
				
			
			
		}
		else if(right!=nullptr && comparator->compare(this->data, item) < 0)
		{
			
			return right->replace(item);
				
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

template<typename T>
inline bool AVLTree<T>::remove(const T item) // Code was written with assistance from Teaching Assistants, Zachary Henson, and Dr. Sridhar's slides.
{
	if (empty)
	{
		return false;
	}
	if (comparator->compare(this->data, item) == 0)
	{
		if ((left == nullptr || left->empty) && (right == nullptr || right->empty))
		{
			empty = true; // The boolean value must be set to true when tree is empty
		}
		else if ((left == nullptr || left->empty) && (right != nullptr && !right->empty))
		{
			data = right->data;
			delete right;
			right = nullptr;
			diff--;
		}
		else if ((right == nullptr || right->empty) && (left != nullptr && !left->empty))
		{
			data = left->data;
			delete left;
			left = nullptr;
			diff++;
		}
		else  // if both left and right child is present
		{
			AVLTree<T>* farthestLeft=right;
			int oldRightDiff = right->diff;
			while (farthestLeft->left != nullptr) // the extreme left child of the right child must be swapped with the root
			{
				farthestLeft = farthestLeft->left;
			}
			data = farthestLeft->data;
			right->remove(farthestLeft->data);
			if (oldRightDiff != right->diff && right->diff == 0)
			{
				diff--;
			}

		}
		
	}
	if (comparator->compare(this->data, item) > 0)
	{
		if (left == nullptr)
		{
			return false;
		}
		else
		{
			int oldLeftDiff = left->diff;
			if (left->remove(item))
			{
				if (oldLeftDiff != left->diff && left->diff == 0)
				{
					diff++; //since left is taken as negative, removing a left child increases diff.
				}
				// if left child is empty, delete it
				if(left->empty)
				{
					delete left;
					left = nullptr;
				}
			}
			else
			{
				return false;
			}
		}
	}
	if (comparator->compare(this->data, item) < 0)
	{
		if (right == nullptr)
		{
			return false;
		}
		else
		{
			int oldRightDiff = right->diff;
			if (right->remove(item))
			{
				if (oldRightDiff != right->diff && right->diff == 0)
				{
					diff--; //right is positive, therefore removal of right child decreases diff
				}
				// if right child is empty, delete it
				if (right->empty)
				{
					delete right;
					right = nullptr;
				}
			}
			else
			{
				return false;
			}
		}
	}
	size--;
	rebalance();
	return true;

}

template<typename T>
inline bool AVLTree<T>::contains(T item) const

{
	if (empty)
	{
		return false;
	}
	if (comparator->compare(item, this->data) == 0)
	{
		return true;
	}
	else if (left!=nullptr && comparator->compare(item, this->data) < 0)
	{
		return left->contains(item);
	}
	else if (right!=nullptr && comparator->compare(item, this->data) > 0)
	{
		return right->contains(item);
	}
	
	return false;

}

template<typename T>
inline T AVLTree<T>::find(const T item) const
{
	
	if (!empty)
	{
		if (comparator->compare(item, this->data) == 0)
		{
			return this->data;
			
		}
		else if (left!=nullptr && comparator->compare(item, this->data) < 0)
		{ 
			return left->find(item);
		}
		else if((right != nullptr && comparator->compare(item, this->data) > 0))
		{
			return right->find(item);
		}
		else
		{
			throw new ExceptionAVLTreeAccess;
		}
		
	}
	else
	{
		throw new ExceptionAVLTreeAccess;
	}
	
}

template<typename T>
inline unsigned long AVLTree<T>::getSize() const
{
	return size;
}

template<typename T>
inline AVLTreeEnumerator<T> AVLTree<T>::enumerator(AVLTreeOrder order) const
{
	return AVLTreeEnumerator<T>(this, order);

}

#endif // !AVL_TREE
