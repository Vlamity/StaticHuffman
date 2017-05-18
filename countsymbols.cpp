#include <iostream>
#include "countsymbols.h"



std::vector <int> SymbolsCount(std::ifstream &fIn)
{
    if(!fIn.is_open())
    {
        std::cerr << "Input file cant be open!" << std::endl;
        return std::vector <int> ();
    }
    std::vector <int> symbol(256);
    char c;
    //for(int i = 0; i < 255; ++i){ symbol[i] = 0;}
    while(!fIn.eof())
    {
        c = fIn.get();
        symbol[c]++;
    }
    return symbol;
}


int SymbolsPrint(std::vector <int> symbol)
{
    if (symbol.empty())
    {
        std::cerr << "Vector is empty" << std::endl;
        return 0;
    }
    int counter = 0;
    for (int i = 0; i < 256; ++i)
    {
        if(symbol[i] != 0)
        {
            counter += symbol[i];
            std::cout << i << ":  "<< symbol[i] << std::endl;
        }
    }
    //std::cout << "COUNTER = " << counter << std::endl;
    return counter;
}
