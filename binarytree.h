/**********************************************************************************************************
CSCI 340 - Assignment 07 - Fall 2020

Programmer: Leonart Jaos
Z-ID: z1911688
Section: 0002
TA: Saiteja Alubelli
Date Due: October 28, 2020

Purpose: The following is the headerfile for a program that allows the implementation of a templated binary
tree as a class. The tree has the capability of insertion, determining height of the tree, and determining
the size of the tree. The class also allows for in order traversal of its nodes with function implementat-
ion within the traversal. 

***********************************************************************************************************/
#ifndef H_BINARYTREE
#define H_BINARYTREE

#include "node.h"

// Since the following tree is a binary tree and not a binary search tree, I used the following logic prov-
// ided in the assignment details to determine the position of the inserted value
typedef enum {left_side, right_side } SIDE;

SIDE rnd()
{
	return rand()%2 ? right_side : left_side;
};

template <typename T> class BinaryTree{

public:
    BinaryTree();                                      // default constructor
    unsigned     getSize() const;                      // returns size of tree
    unsigned     getHeight() const;                    // returns height of tree
    virtual void Insert(const T &v);                     // inserts node in tree
    void         Inorder(void (*fptr)(const T &));          // inorder traversal of tree

protected:
    Node<T> *root;                                      // root of tree

private:
    unsigned _getSize(Node<T>* n) const;                 // private version of getSize()
    unsigned _getHeight(Node<T>* n) const;               // private version of getHeight()
    void     _Insert(Node<T> * &n, const T &v);             // private version of Insert()
    void     _Inorder(Node<T> *n, void (*fptr)(const T &));   // private version of Inorder()
};
// default constructor
template <typename T>
BinaryTree<T>::BinaryTree()
{
	root = NULL;
};
// if the root is NULL, the size is 0
// otherwise recursion is used on each branch until NULL is achieved and adds 1 each time
template <typename T>
unsigned BinaryTree<T>::_getSize(Node<T>* n) const
{
	if(n == NULL)
	{	
		return 0;
	}
	else
		return(_getSize(n->left) + 1 + _getSize(n->right));
};
// a public member function that allows the user to view private member data, but not
// change it
template <typename T>
unsigned BinaryTree<T>::getSize() const
{
	return(_getSize(root));
};
// inserts a node randomly with the value stored at v
// if the node is empty, allocates new memory
template <typename T>
void BinaryTree<T>::_Insert(Node<T> * &n, const T &v)
{
	if(n == NULL)
	{
		n = new Node<T>(v);
	}
	else if(rnd() == left_side)
	{
		_Insert(n->left,v);
	}
	else
	{
		_Insert(n->right,v);
	}
}
// public access of insert that doesn't allow user to alter other values in the tree
template <typename T>
void BinaryTree<T>::Insert(const T &v)
{
	_Insert(root,v);
};
// uses recursion to find which subtree is longer to return the max depth of the
// tree. Adds 1 for every level, assumed root height is 1
template <typename T>
unsigned BinaryTree<T>::_getHeight(Node<T>* n) const
{
	if(n == NULL)
	{
		return 0;
	}
	else
	{
		unsigned ldepth = _getHeight(n->left);
		unsigned rdepth = _getHeight(n->right);
		if(ldepth > rdepth)
			return(ldepth + 1);
		else
			return(rdepth + 1);
	}
};
// public access of protected class data 
template <typename T>
unsigned BinaryTree<T>::getHeight() const
{
	return(_getHeight(root));
};
// inorder traversal of tree, performs function passed with data from
// node passed as parameter
template <typename T>
void BinaryTree<T>::_Inorder(Node<T> *n, void (*fptr)(const T &))
{
	if(n != NULL)
	{
		_Inorder(n->left,fptr);
		fptr(n->data);
		_Inorder(n->right,fptr);
	}
};
// public access of Inorder 
template <typename T>
void BinaryTree<T>::Inorder(void (*fptr)(const T &))
{
	_Inorder(root,fptr);
};
#endif // End of H_BINARYTREE
