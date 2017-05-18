#ifndef COUNTSYMBOLS_H
#define COUNTSYMBOLS_H

#include <vector>
#include <fstream>

std::vector <int> SymbolsCount(std::ifstream &f);
int SymbolsPrint(std::vector <int> symbol);

#endif // COUNTSYMBOLS_H
