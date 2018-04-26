#include<iostream>
#include "utile.h"

using namespace std;

vector<int> string_to_intvec(string str)
{
    vector<int> vec;
    string tmp = "";
    for(size_t i = 0; i < str.size(); i++)
    {
        if(str[i] == ' ')
        {
            vec.push_back(stoi(tmp));
            tmp = "";
        }
        else if(str[i] >= '0' && str[i] <= '9')
        {
            tmp += str[i];
        }
        else
        {
            cerr << "Erreur de lecture: pas un nombre\n";
            exit(1);
        }
    }
    vec.push_back(stoi(tmp));
    return vec;
}