#ifndef NODE_H
#define NODE_H

//YOU MAY NOT MODIFY THIS DOCUMENT

#pragma once

#include "NodeInterface.h"
#include <iostream>

class Node: public NodeInterface{
	friend class BST;
public:

	Node *left, *right;
	int value;


	Node(int val) 
	{
		value = val;
		left = NULL;
		right = NULL;
	}
	virtual ~Node() {}

	/*
	* Returns the data that is stored in this node
	*
	* @return the data that is stored in this node.
	*/
	int getData() const
    {
        return value;
    }

	/*
	* Returns the left child of this node or null if it doesn't have one.
	*
	* @return the left child of this node or null if it doesn't have one.
	*/
	NodeInterface * getLeftChild() const
    {
        return left;
    }

	/*
	* Returns the right child of this node or null if it doesn't have one.
	*
	* @return the right child of this node or null if it doesn't have one.
	*/
	NodeInterface * getRightChild() const
    {
		return right;
    }

	void setLeftChild(Node *n)
	{
		left = n;
	}


	void setRightChild(Node *n)
	{
		right = n;
	}


};

#endif