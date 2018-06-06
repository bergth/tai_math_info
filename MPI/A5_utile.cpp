#include<iostream>
#include<cstdlib>
#include "A5_utile.h"

using namespace std;

vector<int> u_string_to_intvec(string str)
{
    vector<int> vec;
    string tmp = "";
    for(size_t i = 0; i < str.size(); i++)
    {
        if(str[i] == ' ' && tmp != "")
        {
            vec.push_back(u_stoi(tmp));
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
    if(tmp != "")
        vec.push_back(u_stoi(tmp));
    return vec;
}

std::string u_to_string(int val)
{
    if(val == 0)
    {
        return "0";
    }
    string tmp = "";
    while(val != 0)
    {
        tmp += (val % 10) + '0';
        val = val / 10;
    }
    string res = "";
    for(int i = tmp.size() - 1 ; i >= 0; i--)
    {
        res += tmp[i];
    }
    return res;
}

std::string u_to_nstring(int val, size_t n)
{
    string tmp = u_to_string(val);
    if(tmp.size() < n)
    {
        for(size_t i = 0; i < n - tmp.size(); i++)
        {
            tmp.insert(tmp.begin(),'0');
        }
    }
    return tmp;
}

int u_stoi(const std::string& str)
{
    if(str == "")
    {
        cerr << "stoi: empty string" << endl;
        exit(1);
    }
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

std::vector<string> string_to_strvec(std::string str)
{
    vector<string> nvec;
    string str_tmp = "";
    for(size_t i = 0; i < str.size(); i++)
    {
        if(str[i] == ' ')
        {
            nvec.push_back(str_tmp);
            str_tmp = "";
        }
        else
        {
            str_tmp += str[i];
        }
    }
    if(str_tmp != "" && str_tmp != " ")
        nvec.push_back(str_tmp);
    return nvec;
}