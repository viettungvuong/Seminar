#include <iostream>

using namespace std;

class BTreeNode
{
    int sizeNums = 0;
    int *nums;
    int degree = 0;
    BTreeNode **children;
    bool isLeaf()
    {
        return ((degree > 0) ? 0 : 1);
    }
    BTreeNode *search(const int &x)
    {
        int i = 0;
        while (i < sizeNums && x < nums[i])
            i++;
        if (x == nums[i])
            return this; // tra ve so hien tai
        if (this->isLeaf())
            return nullptr; // tuc kh co child thi tra ve null
        return children[i]->search(x);
    }
    void insert(const int &x)
    {
    }
};