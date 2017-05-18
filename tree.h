#ifndef TREE_H
#define TREE_H

#include <vector>


class tree
{
private:
    unsigned char zn;
    int weight;
public:
    tree * lson;
    tree * rson;
    unsigned char getZn();
    int getW();
    void setZn(unsigned char z);
    void setW(int w);
    tree();
    tree(tree * ls, tree * rs);
};

tree * BuildTree(std::vector <int> symbol);

struct Sort
{
    bool operator()(tree * l, tree * r) const
        {return (l -> getW()) < (r -> getW());}
};

#endif // TREE_H
