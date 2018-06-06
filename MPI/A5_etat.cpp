#include <iostream>
#include <algorithm>
#include <queue>
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

string Trs::get_str() const
{
    return from->get_label() + " -> " + tr + " -> " + to->get_label();
}

string Trs::get_str_minimisation(const char c) const
{
    return from->get_label() + " -> " + tr + " -> " + to->get_label() + " = " + c;
}

Etat::Etat(vector<int> _labels, bool _ini, bool _ter, bool _aminimal): labels(_labels), ini(_ini), ter(_ter), aminimal(_aminimal) {}



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
    string str = "";
    if(aminimal)
    {
        str += "[";
    }
    else
    {
        str += "{";
    }
    for(size_t i = 0; i < labels.size(); i++)
    {
        if(labels[i] == -1)
        {
            str += 'P';
        }
        else if(labels[i] == -2)
        {
            str += 'I';
        }
        else
        {
            str += u_to_string(labels[i]);
        }
        if(i + 1 != labels.size())
        {
            str += ", ";
        }
    }
    if(aminimal)
    {
        str += "]";
    }
    else
    {
        str += "}";
    }    return str;
}

void Etat::afficher_etat(int nb_symboles) const
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
    for(char c = 'a' ;  c < (char)('a' + nb_symboles); c++)
    {
        vector<Trs*> tmp = get_trs(c);
        cout << "   - " << tmp.size() << " transitions en " << c << endl;
        for(size_t i = 0; i < tmp.size(); i++)
        {
            cout << "       - " << tmp[i]->get_str() << endl;
        }
    }
    cout << endl;
}

void Etat::afficher_etat_minimisation(int nb_symboles, vector<char> trsSousPart) const
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
    for(char c = 'a' ;  c < (char)('a' + nb_symboles); c++)
    {
        vector<Trs*> tmp = get_trs(c);
        cout << "   - " << tmp.size() << " transitions en " << c << endl;
        for(size_t i = 0; i < tmp.size(); i++)
        {
            cout << "       - " << tmp[i]->get_str_minimisation(trsSousPart[c - 'a']) << endl;
        }
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

std::vector<Trs*> Etat::get_prec() const
{
    return prec;
}

std::vector<Trs*> Etat::get_trs(char c) const
{
    vector<Trs*> n;
    for(size_t i = 0; i < succ.size(); i++)
    {
        if(c == succ[i]->tr)
            n.push_back(succ[i]);
    }
    return n;
}


void Etat::set_old(std::vector<Etat*> ets)
{
    old = ets;
}


std::vector<Etat*> Etat::get_old() const
{
    return old;
}

Etat* epsilon_cloture(vector<Etat*> et)
{
    vector<Etat*> find;
    queue<Etat*> q;
    vector<Trs*> tr;
    for(size_t i = 0; i < et.size(); i++)
    {
        q.push(et[i]);
        find.push_back(et[i]);
    }
    while(!q.empty())
    {
        tr = q.front()->get_succ();
        q.pop();
        for(size_t i = 0; i < tr.size(); i++)
        {
            if(tr[i]->tr == '*')
            {
                Etat* to = tr[i]->to;
                if(!find_etat(find,to))
                {
                    find.push_back(to);
                    q.push(to);
                }
            }
        }
    }
    return contact_name_etat(find);
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
        }
    }
    std::sort(labels.begin(),labels.end());

    if(labels.size() == 0)
        return NULL;
    Etat* res = new Etat(labels,ini,ter,false);
    res->set_old(ets);

    return res;
}

vector<Etat*> get_old_transitions(const Etat* et, char c)
{
    vector<Etat*> net;
    vector<Etat*> old = et->get_old();
    for(size_t j = 0; j < old.size(); j++)
    {
        vector<Trs*> succ = old[j]->get_succ();
        for(size_t i = 0; i < succ.size(); i++)
        {
            if(succ[i]->tr == c)
                net.push_back(succ[i]->to);
        }
    }
    return net;
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

std::string Etat::get_name_old()
{
    string res = "";
    for(size_t i = 0; i < old.size(); i++)
    {
        res += old[i]->get_label();
        if(i != old.size() - 1)
        {
            res += ", ";
        }
    }
    return res;
}
