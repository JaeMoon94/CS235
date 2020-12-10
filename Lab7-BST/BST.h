#ifndef BST_H
#define BST_H

#include "BSTInterface.h"

//YOU MAY NOT MODIFY THIS DOCUMENT

#pragma once

#include "Node.h"

using namespace std;

class BST : public BSTInterface {
private:
    Node *root;
public: 
	BST() 
    {
        root = NULL;
    }
	virtual ~BST() {clear();}

	//Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

	/*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	NodeInterface * getRootNode() const
    {
        return root;
    }

	/*
	* Attempts to add the given int to the BST tree
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool add(int data)
    {
       return insert(root,data);
    }

	/*
	* Attempts to remove the given int from the BST tree
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool remove(int data)
    {   
        return deleteBranch(root,data);
    }

	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	void clear()
    {
        clearAll(root);
        root = NULL;
    }
    
    bool insert(Node *&x, int data)
    {
        if(x == NULL)
        {
            Node *newNode = new Node(data);
            x = newNode;
            return true; 
        }

        if(x -> value > data)
        {
            return insert(x->left,data);
        }

        if(x -> value < data)
        {
            return insert(x->right,data);
        }

        return false;
    }

    bool deleteBranch(Node *&x, int data)
    {
        if(x == NULL)
        {
            return false;
        }

       if(data < x->value)
       {
           return deleteBranch(x->left,data);
       }

       else if(data > x->value)
       {
           return deleteBranch(x->right,data);
       }
       else
       {
           if(x->left == NULL)
           {
               Node *temp = x->right;
               delete x;
               x = temp;
               return true;
           }
           else if(x->right == NULL)
           {
               Node *temp = x->left;
               delete x;
               x = temp;
               return true;
           }
       }

        Node* temp = x->left;
        Node* parent = x;
        while (temp->right != NULL) //two children.
        {
            parent = temp;
            temp = temp->right;
        }
        if (x->value != parent->value)
        {
            parent->right = temp->left;
        }
        else parent->left = temp->left;

            x->value = temp->value;
        delete temp;
        return true;
    }

    void clearAll(Node* x)
    {
        if (x == NULL)
        {
            return;
        }

        if (x->left != NULL)
        {
            clearAll(x->left);
        }

        if (x->right != NULL)
        {
            clearAll(x->right);
        }

        delete x;
        return;
    }
   

};

#endif


    // int size(Node *x)
    // {
    //     if(x == NULL) return 0;
    //     Node *left 
    //     Node *right = size(x->left) + size(x->right)
    //     size(x->left) + size(x->right)

    //     return 1 + size(x->left) + size(x->right);
    // }


    ////// Pre order
    // void print(Node *n)
    // {
    //     if(n == NULL) return;
    //     cout << n->value << " " ;
    //     print(n->left);

    //     print(n->right);
    // }

    //////post order traversal
    // void print(Node *n)
    // {
    //     if(n == NULL) return;
    //     print(n->left);
    //     print(n->right);

    //     cout << n->value << " " ;
    // }


    ////Indorer traversal

    // void print(Node *n)
    // {
    //     if(n == NULL) return;
    //     print(n->left);
    //     cout << n->value << " " ;
    //     print(n->right);
    // }