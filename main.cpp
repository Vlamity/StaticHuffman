#include <iostream>
#include <fstream>
#include <netinet/in.h>
#include "countsymbols.h"
#include "tree.h"
#include "coding.h"
using namespace std;

extern vector <bool> code;
extern map <char,  vector<bool> > coding;


int main(int argc, char * argv[])
{
    if(argc != 4)
    {
        cerr << "Incorrect number of command-line arguments.\nRequired format: ./main InputFile -key OutputFile\nKeys:\n\"-a\": archive\n\"-u\": unarchive\n";
        return 1;
    }
    ifstream fIn;
    fIn.open(argv[1], ios::binary);
    if(!fIn.is_open())
    {
        cerr << "Input file can't be open!\nRequired format: ./main InputFile -key OutputFile\nKeys:\n\"-a\": archive\n\"-u\": unarchive\n";
        return 1;
    }
    string key = argv[2];
    if(!(key[0] == '-' && key.size() == 2 && (key[1] == 'a' || key[1] == 'u')))
    {
        cerr << "Invalid key!\nRequired format: ./main InputFile -key OutputFile\nKeys:\n\"-a\": archive\n\"-u\": unarchive\n";
        return 1;
    }
    unsigned char c;
    if(key[1] == 'a') //Архивация
    {
        vector <int> symbol(256); //Массив, показывающий, сколько раз каждый символ встречается в файле
        //Сбор статистики
        while(fIn.peek() != EOF)
        {
            c = fIn.get();
            symbol[c]++;
        }
        fIn.seekg(0);
        int counter = SymbolsPrint(symbol);   //Вывод на экран статистики встречаемости символов
        tree * root = BuildTree(symbol);    //Построение дерева
        BuildCoding(root);    //Построение ассоциаций символ:код
        ofstream fOut;
        fOut.open(argv[3], ios::binary);
        fOut.write("HUFF",4);
        cout << endl << "Writing statistics to file..." << endl;
        for (int i = 0; i < 256; ++i)
        {
            uint32_t num = htonl(symbol[i]);
            fOut.write((char*)&num, 4);
        }
        cout << "Done." << endl;
        cout << "Writing encoded data to file..." << endl;
        char b = 0;
        int check = 0;
        while(fIn.peek() != EOF)
        {
            c = fIn.get();
            vector <bool> cd = coding[c];
            for(int i = 0; i != cd.size(); ++i)
            {
                b = b | (cd[i] << (7-check));
                ++check;
                if(check == 8)
                {
                    fOut << b;
                    b = 0;
                    check = 0;
                }
            }
        }
        while(check != 8)
        {
            b = b | 0;
            ++check;
        }
        fOut << b;
        cout << "Done." << endl;
        fIn.close();
        fOut.close();
    }
    else //Разархивация
    {
        char ch[4];
        for(int i = 0; i < 4; ++i)
        {
            ch[i] = fIn.get();
        }
        if(!((ch[0] == 'H') && (ch[1] == 'U') && (ch[2] == 'F') && (ch[3] == 'F')))
        {
            cerr << "Invalid coded file" << endl;
            return 1;
        }
        vector <int> symbol(256); //Массив, показывающий, сколько раз каждый символ встречается в файле
        for(int i = 0; i < 256; ++i)
        {
            uint32_t num;
            fIn.read((char*)&num, 4);
            symbol[i] = ntohl(num);
        }
        int counter = SymbolsPrint(symbol);   //Вывод на экран статистики встречаемости символов
        tree * root = BuildTree(symbol);    //Построение дерева
        BuildCoding(root);    //Построение ассоциаций символ:код
        ofstream fOut;
        fOut.open(argv[3], ios::binary);
        tree * t = root;
        int check = 0;
        char byte;
        bool b;
        byte = fIn.get();
        while(counter != 0)
        {
            b = byte & (1 << (7 - check) ) ; //Просмотр битов в байте
            if (b) //1 - идём по дереву вправо
            {
                t = t -> rson;
            }
            else //0 - влево
            {
                t = t -> lson;
            }
            if (t -> lson == NULL && t -> rson == NULL)
            {
                fOut << t->getZn();
                t = root;
                --counter;
            }
            ++check;
            if (check == 8)
            {
                check = 0;
                byte = fIn.get();
            }
        }
        cout << endl;
        fIn.close();
        fOut.close();
    }
}
