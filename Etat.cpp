#include "Etat.h"
using namespace std;

string Etat::get_label()
{
    string str = "{";
    for(size_t i = 0; i < labels.size(); i++)
    {
        str += to_string(labels[i]);
        if(i + 1 != labels.size())
        {
            str += ", ";
        }
    }
    str += "}";
    return str;
}

        