#include <iostream>
#include <algorithm>
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

Trs::Trs(Etat* _from, char _tr, Etat* _to)
{
    from = _from;
    tr = _tr;
    to = _to;
}

void Trs::afficher() const
{
        cout << from->get_label() << " -> ";
        cout << tr << " -> ";
        cout << to->get_label();
        cout << endl;
}

Etat::Etat(vector<int> _labels, bool _ini, bool _ter): labels(_labels), ini(_ini), ter(_ter) {}


int Etat::operator<(const Etat& right) const
{
    return labels < right.get_vect_label();
}

int Etat::operator==(const Etat& right) const
{
    return labels == right.get_vect_label();
}


int compare_etat_pt(const Etat* a, const Etat* b)
{
    return *a < *b;
}

string Etat::get_label() const
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

void Etat::afficher_etat() const
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
    cout << "Transitions: " << endl;
    for(size_t i = 0; i < succ.size(); i++)
    {
        cout << "   - ";
        succ[i]->afficher();
    }
    cout << endl;
}

void Etat::set_ter(bool _ter)
{
    ter = _ter;
}

bool Etat::get_ter()
{
    return ter;
}

bool Etat::get_ini()
{
    return ini;
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
    succ.push_back(_succ);
}

vector<int> Etat::get_vect_label() const
{
    return labels;
}

void Etat::sort()
{
    std::sort(succ.begin(),succ.end(),compare_trs_pt);
    std::sort(prec.begin(),prec.end(),compare_trs_pt);
}

std::vector<Trs*> Etat::get_succ() const
{
    return succ;
}


Etat* contact_name_etat(vector<Etat*> ets)
{
    vector<int> labels;
    bool ini = false;
    bool ter = false;
    std::vector<int>::iterator it;
    for(size_t i = 0; i < ets.size(); i++)
    {
        vector<int> tmp = ets[i]->get_vect_label();
        for(size_t j = 0; j < tmp.size(); j++)
        {
            int tmp_label = tmp[j];
            it = find(labels.begin(),labels.end(),tmp_label);
            if(it == labels.end())
            {
                labels.push_back(tmp_label);
            }
            if(ets[i]->get_ter())
                ter = true;
            if(ets[i]->get_ini())
            {
                ini = true;
            }
        }
    }
    std::sort(labels.begin(),labels.end());

    if(labels.size() == 0)
        return NULL;
    Etat* res = new Etat(labels,ini,ter);


    return res;
}

Etat* get_transitions(const Etat* et, char c)
{
    vector<Etat*> net;
    vector<Trs*> succ = et->get_succ();
    for(size_t i = 0; i < succ.size(); i++)
    {
        if(succ[i]->tr == c)
            net.push_back(succ[i]->to);
    }

    return contact_name_etat(net);
}

Etat* find_etat(const vector<Etat*>& ets, Etat* et)
{
        for(size_t i = 0; i < ets.size();i++)
        {
            if(*(ets[i]) == *et)
            {
                return ets[i];
            }
        }
        return NULL;
}