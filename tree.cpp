#include "tree.h"
#include <list>
#include <fstream>
#include <iostream>

using namespace std;


unsigned char
tree::getZn()
{
    return zn;
}

int
tree::getW()
{
    return weight;
}
void
tree::setZn(unsigned char z)
{
    zn = z;
}

void
tree::setW(int w)
{
    weight = w;
}

tree::tree()
{
    weight = 0;
    zn = char(0);
    lson = nullptr;
    rson = nullptr;
}

tree::tree(tree * ls, tree * rs)
{
    zn = char(0);
    weight = ls -> getW() + rs -> getW();
    lson = ls;
    rson = rs;
}



tree * BuildTree(vector <int> symbol)
{
    list <tree*> L;
    for(int i = 0; i < 256; ++i)
    {
        tree * p = new tree;
        if(symbol[i] != 0)
        {
            p -> setZn(i);
            p -> setW(symbol[i]);
            L.push_back(p);
        }
    }
    //Построение дерева
    while(L.size() != 1)
    {
        L.sort(Sort());
        tree * ls = L.front();
        L.pop_front();
        tree * rs = L.front();
        L.pop_front();
        tree * parent = new tree(ls, rs);
        L.push_front(parent);
    }
    tree * root = L.front();
    return root;
}
