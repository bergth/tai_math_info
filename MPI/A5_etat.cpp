#include "A5_etat.h"
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

void Etat::set_ter(bool _ter)
{
    ter = _ter;
}

void Etat::set_ini(bool _ini)
{
    ini = _ini;
}

void Etat::add_prec(tr_t* _prec)
{
    prec.push_back(_prec);
}

void Etat::add_succ(tr_t* _succ)
{
    prec.push_back(_succ);
}
