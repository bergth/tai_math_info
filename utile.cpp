#include "utile.h"

using namespace std;

std::tuple<int,int,int> string_to_tupple(std::string str)
{
    tuple<int,int,int> tup;
    size_t size_str = str.size();

    string tmp = "";
    size_t i = 0;
    for(; i < size_str && str[i] != ' '; i++)
    {
        tmp += str[i];
    }
    get<0>(tup) = stoi(tmp,nullptr,10);
    i++;

    string tmp = "";
    for(; i < size_str && str[i] != ' '; i++)
    {
        tmp += str[i];
    }
    get<1>(tup) = stoi(tmp,nullptr,10);
    i++;

    string tmp = "";
    for(; i < size_str && str[i] != ' '; i++)
    {
        tmp += str[i];
    }
    get<2>(tup) = stoi(tmp,nullptr,10);
}