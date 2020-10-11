#pragma once
#ifndef AVL_TREE_ENUMERATOR
#define AVL_TREE_ENUMERATOR

#include <stack>
#include "Enumerator.h"
#include "AVLTreeOrder.h"
#include "AVLTree.h"

template <typename S>
class AVLTree;

template <typename T>
class AVLTreeEnumerator : public Enumerator<T>
{
private:
	AVLTreeOrder order;
	std::stack<const AVLTree<T>*> traversalStack;
	void buildTraversalStack(const AVLTree<T>* current);
public:
	AVLTreeEnumerator(const AVLTree<T>* root, AVLTreeOrder order = AVLTreeOrder::inorder);
	virtual ~AVLTreeEnumerator();
	bool hasNext() const;
	T next();                        // throws ExceptionEnumerationBeyondEnd if no next item is available
	T peek() const;                  // throws ExceptionEnumerationBeyondEnd if no next item is available
	AVLTreeOrder getOrder();         // returns the order of this enumerator (preorder, inorder, or postorder)
};

// Add your implementation below this line.




template<typename T>
inline void AVLTreeEnumerator<T>::buildTraversalStack(const AVLTree<T>* current) // stack is last in first out, therefore elements must be inserted in backward order to ensure correct order of enumeration.
{
	if (current == nullptr || current->empty)
	{
		return;
	}
	if (order == AVLTreeOrder::preorder) // Written with help from Cameron Bost
	{
		
			buildTraversalStack(current->right);
			buildTraversalStack(current->left);
			traversalStack.push(current);
		
	
	}
	else if (order == AVLTreeOrder::postorder)
	{
		traversalStack.push(current);
		buildTraversalStack(current->right);
		buildTraversalStack(current->left);
	}
	else
	{
		buildTraversalStack(current->right);
		traversalStack.push(current);
		buildTraversalStack(current->left);
	}
}

template<typename T>
inline AVLTreeEnumerator<T>::AVLTreeEnumerator(const AVLTree<T>* root, AVLTreeOrder order)
{
	
	if(!root->empty)
	{
		
		this->order = order;
		buildTraversalStack(root); //the traversal stack is built only if the tree is not empty
	}
	

	
}

template<typename T>
inline AVLTreeEnumerator<T>::~AVLTreeEnumerator()
{
}

template<typename T>
inline bool AVLTreeEnumerator<T>::hasNext() const
{
	if (!traversalStack.empty())
	{
		return true;
	}

	else
	{
		return false;
	}
}


template<typename T>
inline T AVLTreeEnumerator<T>::next()
{
	T item;
	if (!traversalStack.empty())
	{
		 item = traversalStack.top()->data;
		 traversalStack.pop();
		
	}
	else
	{
		throw new ExceptionEnumerationBeyondEnd;
	}
	return item;
	
	
}

template<typename T>
inline T AVLTreeEnumerator<T>::peek() const
{
	if (!traversalStack.empty())
	{
		T item = traversalStack.top()->data; //operation only accesses data without actually moving the pointer to the next node.
		return item;
	}
	else
	{
		throw new ExceptionEnumerationBeyondEnd;
	}
}

template<typename T>
inline AVLTreeOrder AVLTreeEnumerator<T>::getOrder()
{
	return order;
}
#endif // 