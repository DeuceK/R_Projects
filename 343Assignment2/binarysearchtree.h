// BinarySearchTree class
// Creates a BST to store values
// Uses BinaryNode which holds the data
// Uses templates to store any type of data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "binarynode.h"

using namespace std;

template<class ItemType>
class BinarySearchTree 
{
    struct node 
    {
        ItemType data;
        node* left;
        node* right;
    };
    node* root;

    node* clear(node* n) 
    {
        if(n == NULL)
            return NULL;
        {
            clear(n->left);
            clear(n->right);
            delete n;
        }
        return NULL;
    }

    node* placeNode(ItemType x, node* n)
    {
        if(n == NULL)
        {
            n = new node;
            n->data = x;
            n->left = n->right = NULL;
        }

        else if(x < n->data)
        {
            n->left = placeNode(x, n->left);
        }
        else if(x > n->data)
        {
            n->right = placeNode(x, n->right);
        }
        return n;
    }

    node* getMinimum(node* n)
    {
        if(n == NULL)
        {
            return NULL;
        }
        else if(n->left == NULL)
        {
            return n;
        }
        else
        {
            return getMinimum(n->left);
        }
    }

    node* getMaximum(node* n) 
    {
        if(n == NULL)
        {
            return NULL;
        }
        else if(n->right == NULL)
        {
            return n;
        }
        else
        {
            return getMaximum(n->right);
        }
    }

    node* deletion(ItemType x, node* n) 
    {
        node* temp;
        if(n == NULL)
        {
            return NULL;
        }
        else if(x < n->data)
        {
            n->left = deletion(x, n->left);
        }
        else if(x > n->data)
        {
            n->right = deletion(x, n->right);
        }
        else if(n->left && n->right)
        {
            temp = getMinimum(n->right);
            n->data = temp->data;
            n->right = deletion(n->data, n->right);
        }
        else
        {
            temp = n;
            if(n->left == NULL)
            {
                n = n->right;
            }
            else if(n->right == NULL)
            {
                n = n->left;
            }
            delete temp;
        }

        return n;
    }

    void print(node* n) const
    {
        if(n == NULL)
        {
            return;
        }
        print(n->left);
        cout << n->data << " ";
        print(n->right);
    }

    node* findNode(node* n, ItemType x) const
    {
        if(n == nullptr)
        {
            return n;
        }
        else if(x < n->data)
        {
            return findNode(n->left, x);
        }
        else if(x > n->data)
        {
            return findNode(n->right, x);
        }
        else
        {
            return n;
        }
    }

    int numberOfNodes(node* n, int count) const
    {
        if(n == NULL)
        {
            return count;
        }
        count++;
        return numberOfNodes(n->left, count);
        return numberOfNodes(n->right, count);
    }

    int getHeight(node* n) const
    {
        if(n == NULL)
        {
            return 0;
        }
        else
        {
            int leftNodes = getHeight(n->left);
            int rightNodes = getHeight(n->right);
            if(leftNodes >= rightNodes)
            {
                return leftNodes + 1;
            }
            else
            {
                return rightNodes + 1;
            }
        }
    }

    vector<ItemType> copyToArray(node* n, vector<ItemType> arr)
    {
        if(n == NULL)
        {
            return arr;
        }
        copyToArray(n->left, arr);
        arr.push_back(n->data);
        copyToArray(n->right, arr);
        return arr;
    }


    int mismatchCount(node* first, node* second, int count) const
    {
        if ((first != NULL && second != NULL) && (first->data == second->data))
        {
		    return 0;
        }
	    if ((first == NULL) || (second == NULL))
        {
		    return count++;
        }
	    return ((first->data == second->data) && mismatchCount(first->left, second->left, count) && mismatchCount(first->right, second->right, count));
    }

public:
    // constructor, empty tree
    BinarySearchTree<ItemType>();
    // constructor, tree with root
    explicit BinarySearchTree<ItemType>(const ItemType& rootItem);
    // copy constructor
    BinarySearchTree<ItemType>(const BinarySearchTree<ItemType>& bst);
    // destructor
    virtual ~BinarySearchTree<ItemType>();
    // true if no nodes
    bool isEmpty() const;
    // 0 if empty, 1 if only root, otherwise
    // max height of subtrees + 1
    int getHeight() const;
    // number of nodes and data in tree
    int getNumberOfNodes() const;
    // add a new item
    // return true if succesasfull
    // false if item already in tree or some other reason to fail
    bool add(const ItemType& item);
    // true if item is in tree
    bool contains(const ItemType& item) const;
    // dispaly a sideways ascii representation of tree
    void displaySideways() const;
    // inorder traversal: left-root-right
    // takes a function that takes a single parameter of ItemType
    // the function can modify the data in tree, but the
    // tree structure is not changed
    void inorderTraverse(void visit(ItemType&)) const;
    // create dynamic array, copy all the items to the array
    // and then read the array to re-create this tree
    void rebalance();
    // delete all nodes in tree and set root to nullptr
    void clear();
    // given an array of length n
    // create this tree to have all items in that array
    // with the minimum height
    bool readTree(ItemType arr[], int n);
    // trees are equal if they have the same structure
    // AND the same item values at all the nodes
    bool operator==(const BinarySearchTree<ItemType> &) const;
    // not == to each other
    bool operator!=(const BinarySearchTree<ItemType> &) const;
private:
    // root of the tree
    BinaryNode<ItemType>* rootPtr {nullptr};
    // current node of tree
    BinaryNode<ItemType>* currentPtr {nullptr};
    // add a new node, helper function for add
    BinaryNode<ItemType>* placeNode(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNodePtr);
    // find the node with given vale, helper function for contains
    BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* subTreePtr, const ItemType& target) const;
    // helper function for displaySideways to work recursively
    void sideways(BinaryNode<ItemType>* current, int level) const;
};

#include "binarysearchtree.cpp"
#endif // BINARYSEARCHTREE_H