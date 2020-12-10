#ifndef AVL_H
#define AVL_H

#include "Node.h"
#include "AVLInterface.h"
#include <algorithm>

class AVL : public AVLInterface
{
    private:
        Node* root;

    public:
    AVL() 
    {
        root = NULL;
    }
    virtual ~AVL() 
    {
        clear();
    }

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
    * Attempts to add the given int to the AVL tree
    * Rebalances the tree if data is successfully added
    *
    * @return true if added
    * @return false if unsuccessful (i.e. the int is already in tree)
    */
    bool add(int data)
    {
        return insert(root,data);
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
            bool isvalid = insert(x->left,data);
            rebalance(x,data);
            x->height = updateHeight(x);
            return isvalid;
        }

        else if(x -> value < data)
        {
            bool isvalid = insert(x->right,data);
            rebalance(x,data);
            x->height = updateHeight(x);
            return isvalid;
        }

        else return false;
    }

    /*
    * Attempts to remove the given int from the AVL tree
    * Rebalances the tree if data is successfully removed
    *
    * @return true if successfully removed
    * @return false if remove is unsuccessful(i.e. the int is not in the tree)
    */



    bool remove(int data)
    {
        return deleteBranch(root,data);
    }


    bool deleteBranch(Node *&x, int data)
    {
        if(x == NULL)
        {
            return false;
        }

       if(data < x->value)
       {
           bool isValid = deleteBranch(x->left,data);
           rebalance(x,data);
           x->height = updateHeight(x);
           return isValid;
       }

       else if(data > x->value)
       {
           bool isValid =  deleteBranch(x->right,data);
           rebalance(x,data);
           x->height = updateHeight(x);
           return isValid;
       }
       else
       {
           if(x->left == NULL && x ->right != NULL)
           {
               Node *temp = x->right;
               delete x;
               x = temp;
               rebalance(x,data);
            x->height = updateHeight(x);      
               return true;
           }
           else if(x->right == NULL && x-> left!= NULL)
           {
               Node *temp = x->left;
               delete x;
               x = temp;
               x->height = updateHeight(x);
               rebalance(x,data);
               return true;
           }
           else if(x->right == NULL && x->left == NULL)
           {
               delete x;
               x = NULL;
               return true;
           }
            else{

                Node* temp2 = maxVal(x);  
                x->value = temp2->value;  
                deleteBranch(x->left,temp2->value);
                x->height = updateHeight(x);
                rebalance(x,data);              
            }

         
       }
        // x->height = updateHeight(x);

        return true;
    }


    /*
    * Removes all nodes from the tree, resulting in an empty tree.
    */
    void clear()
    {
        clearAll(root);
        root = NULL;
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

    //Helper Function
    int updateHeight(Node *&x)
    {
        if (x == NULL){
            return 0;
        }
        x->height = 1 + max(updateHeight(x->left), updateHeight(x->right));
        return x->height;
    
    }

    bool rebalance(Node *&x, int data)
    {

        // Left Left Case  
        if (getBalance(x) == -2 && getBalance(x->left) <= 0) {
            rightRotate(x);
            return true;
        }
        // Right Right Case  
        if (getBalance(x) == 2 && getBalance(x->right) >= 0 ) {
            leftRotate(x);
            return true;
        }
        // Left Right Case  
        if (getBalance(x) == -2 && getBalance(x->left) == 1) {
            leftRotate(x->left);
            rightRotate(x);
            return true;
        }
        // Right Left Case  
        if (getBalance(x) == 2 && getBalance(x->right) == -1) {
            rightRotate(x->right);
            leftRotate(x);
            return true;
        }
        return true;
    }
    Node *maxVal(Node* n)  
    {
        Node* node = n->left;
        while (node->right != NULL) {
            node = node->right;
        }
        return node;
    }  

    Node *minVal(Node* n)  
    {  
        Node* temp = n;
        while (temp->left != NULL)  
            temp = temp->left;  
    
        return temp;  
    }  

    Node* rightRotate(Node *&y)
    {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left),
            getHeight(x->right)) + 1;
        y = x;
        return y;
    }

    Node* leftRotate(Node *&x)
    {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(getHeight(x->left),
            getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left),
            getHeight(y->right)) + 1;
        x = y;
        return x;
    }


    int getHeight(Node*& n) {
        if (n == NULL) {
            return 0;
        }        
        return n->height;
    }
    

    int getBalance(Node *n)
    {
        if (n == NULL)
            return 0;
        return getHeight(n->right) - getHeight(n->left);
    }


    bool isContain(Node* x, int val)
    {
        bool isDup = false;
        if(x == NULL) return false;

        if(val == x->value) isDup = true;

        else if(val < x -> value) isDup = isContain(x->left,val);

        else if(val > x -> value) isDup = isContain(x->right, val);

        else isDup = false;

        return isDup;
    }

    bool isDup(int val)
    {
        bool dupCheck;
        if(root == NULL)
        {
            return false;
        }

        else 
        {
            dupCheck = isContain(root, val);
        }

        return dupCheck;
    } 
};

#endif
