#include "Etat.h"
using namespace std;

Etat::Etat(vector<int> _labels, bool _ini, bool _ter): labels(_labels), ini(_ini), ter(_ter) {}

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