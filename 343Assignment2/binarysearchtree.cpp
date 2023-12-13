// stub file
// provided so that the BinarySearchTree can be compiled
// none of the functions are implemented

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() 
{
    root = new node;
}

template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree() 
{
    root = clear(root);
}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem) 
{
    root = new node;
    root->data = rootItem;
}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& bst) 
{
    root = new node;
    root = bst.root;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const 
{
    int count = 0;
    count = numberOfNodes(root, count);
    if(count > 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() const 
{
    int lHeight = getHeight(root->left) + 2;
    int rHeight = getHeight(root->right) + 2;
    if(lHeight >= rHeight)
    {
        return lHeight;
    }
    else
    {
        return rHeight;
    }
}

template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const 
{
    int num = 0;
    num = numberOfNodes(root, num);
    return num;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& item) 
{
    root = placeNode(item, root);
    return true;
}

template<class ItemType>
void BinarySearchTree<ItemType>::clear()
{
    clear(root);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& item) const
{
    ItemType x = item;
    node* buffer = findNode(root, x);
    if(buffer == nullptr)
    {
        return false;
    }
    if(buffer->data == item)
    {
        return true;
    }
    return false;
}

template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType&)) const 
{
    print(root);
}

template<class ItemType>
void BinarySearchTree<ItemType>::rebalance()
{
    vector<ItemType> vect;
    vect = copyToArray(root, vect);
    cout << "[";
    print(root);
    cout << "]" << endl;
}

template<class ItemType>
void BinarySearchTree<ItemType>::displaySideways() const 
{
    print(root);
    cout << endl;
}

template<class ItemType>
void BinarySearchTree<ItemType>::sideways(BinaryNode<ItemType>* current, int level) const 
{
    if (current != NULL) 
    {
        level++;
        sideways(current->getRightChildPtr(), level);

        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--) 
        {
            cout << "    ";
        }

        cout << current->getItem() << endl;        // display information of object
        sideways(current->getLeftChildPtr(), level);
    }
}

template<class ItemType>
bool BinarySearchTree<ItemType>::operator==(const BinarySearchTree<ItemType>& other) const
{
    int count = 0;
    count = mismatchCount(root, other.root, count);
    if(count == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class ItemType>
bool BinarySearchTree<ItemType>::readTree(ItemType arr[], int n) 
{
    vector<ItemType> vect;
    vect = copyToArray(root, vect);
    cout << "[";
    print(root);
    cout << "]" << endl;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::operator!=(const BinarySearchTree<ItemType>& other) const 
{
    int count = 0;
    count = mismatchCount(root, other.root, count);
    if(count > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
