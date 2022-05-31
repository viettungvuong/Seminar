#include <iostream>

using namespace std;

class BTreeNode
{
    int t; // minimum degree
    int sizekeys = 0;
    int *keys;            // nhung so trong node
    int degree = 0;       // so con
    BTreeNode **children; // node con
    BTreeNode(int t)
    {
        this->t = t;
        this->keys = new int[2 * t - 1]; // nhieu nhat la 2t-1
        this->children = new BTreeNode *[2 * t];
    }
    bool isLeaf()
    {
        return ((degree > 0) ? 0 : 1);
    }
    BTreeNode *search(const int &x)
    {
        int i = 0;
        while (i < sizekeys && x < keys[i])
            i++;
        if (x == keys[i])
            return this; // tra ve so hien tai
        if (this->isLeaf())
            return nullptr; // tuc kh co child -> kh chua node tuong ung thi tra ve null
        return children[i]->search(x);
    }
    void splitKeys(int t, BTreeNode *prev)
    {
        sort(this->keys, this->keys + (2 * t));
        int mid = this->keys[(2 * t - 1) / 2];
        int *left, *right;
        left = new int[t - 1];
        right = new int[t - 1];
        for (int i = 0; i < t - 1; i++)
        {
            int j = ((2 * t - 1) / 2) + (i + 1);
            left[i] = this->keys[i];
            right[i] = this->keys[j];
        }
        BTreeNode *leftNode = new BTreeNode(t);
        BTreeNode *rightNode = new BTreeNode(t);
        leftNode->keys = left;
        rightNode->keys = right;
        prev->children[degree] = leftNode;
        prev->children[degree + 1] = rightNode;
        degree += 2;
        // gio phai lam them mid vao prev
        if (sizekeys + 1 < (2 * t + 1))
        {
            prev->keys[sizekeys] = mid;
            sizekeys++;
        } // ta se lap lai buoc split roi add den khi duoc thi thoi
    }
    void addXToNode(const int &x, BTreeNode *node)
    {
    }
    void insert(const int &x)
    {
        if (!this)
        {
            BTreeNode *insert = new BTreeNode(t);
            insert->keys[0] = x;
            insert->sizekeys++;
            return;
        }
        BTreeNode *current = this, *prev = nullptr;
        while (1)
        {
            int i = 0;
            while (i < sizekeys && x < keys[i])
                i++;
            if (x == keys[i]) // so da co, kh add
                return;
            if (current->isLeaf())
            {
                if (sizekeys + 1 < (2 * t - 1))
                {
                    keys[sizekeys] = x;
                    sizekeys++;
                }
                else
                {
                    splitKeys(t, prev);
                }
            }
            else
            {
                prev = current;
                current = children[i];
            }
        }
    }
};