#include <iostream>
#include "A5_etat.h"
using namespace std;

int Trs::operator==(const Trs& right) const
{
    if(from->get_vect_label() != right.from->get_vect_label())
        return false;
    if(tr != right.tr)
        return false;
    if(to->get_vect_label() != right.to->get_vect_label())
        return false;

    return true;
}

int Trs::operator!=(const Trs& right) const
{
    return !(*this == right);
}

int Trs::operator<(const Trs& right) const
{
    if(from->get_vect_label() < right.from->get_vect_label())
    {
        return true;
    }
    else if(from->get_vect_label() == right.from->get_vect_label())
    {
        if(tr < right.tr)
        {
            return true;
        }
        else if(tr == right.tr)
        {
            if(to->get_vect_label() < right.to->get_vect_label())
            {
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}

int Trs::operator<=(const Trs& right) const
{
    return (*this == right) || (*this < right);
}


int Trs::operator>(const Trs& right) const
{
    return !(*this <= right);
}

int Trs::operator>=(const Trs& right) const
{
    return !(*this < right);
}

int compare_trs_pt(const Trs* a, const Trs* b)
{
    return *a < *b;
}

Etat::Etat(vector<int> _labels, bool _ini, bool _ter): labels(_labels), ini(_ini), ter(_ter) {}

string Etat::get_label()
{
    string str = "{";
    for(size_t i = 0; i < labels.size(); i++)
    {
        str += u_to_string(labels[i]);
        if(i + 1 != labels.size())
        {
            str += ", ";
        }
    }
    str += "}";
    return str;
}

void Etat::afficher_etat()
{
    cout << "[" << get_label() << "]-----------" << endl;
    if(ini)
        cout << "I";
    else
        cout << " ";

    if(ter)
        cout << "T";
    else
        cout << " ";
    cout << endl;
}

void Etat::set_ter(bool _ter)
{
    ter = _ter;
}

void Etat::set_ini(bool _ini)
{
    ini = _ini;
}

void Etat::add_prec(Trs* _prec)
{
    prec.push_back(_prec);
}

void Etat::add_succ(Trs* _succ)
{
    prec.push_back(_succ);
}

vector<int> Etat::get_vect_label()
{
    return labels;
}