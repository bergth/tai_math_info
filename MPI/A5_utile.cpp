#include<iostream>
#include<cstdlib>
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

std::string to_string(int val)
{
    string tmp = "";
    while(val != 0)
    {
        tmp += (val % 10) - '0';
        val = val / 10;
    }
    string res = "";
    for(int i = tmp.size() - 1 ; i >= 0; i--)
    {
        res += tmp[i];
    }
    return res;
}

int stoi(const std::string& str)
{
    int res = 0;
    for(size_t i = 0; i < str.size(); i++)
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
            res *= 10;
            res += str[i] - '0';
        }
        else
        {
            cerr << "Erreur parsing stoi" << endl;
            exit(1);
        }
    }
    return res;
}