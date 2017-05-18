#include <fstream>
#include <iostream>
#include <stdio.h>
#include "coding.h"
#include <map>
using namespace std;

vector <bool> code;
map <char,  vector<bool> > coding;

void BuildCoding(tree * root)
{
    if(root -> lson != NULL)
    {
        code.push_back(0);
        BuildCoding(root -> lson);
    }
    if(root -> rson != NULL)
    {
        code.push_back(1);
        BuildCoding(root -> rson);
    }
    if(root -> lson == NULL && root -> rson == NULL)
    {
        coding[root -> getZn()] = code;
    }
    code.pop_back();
}

