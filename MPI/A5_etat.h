#ifndef ETAT_H
#define ETAT_H

#include<vector>
#include<string>
#include "A5_utile.h"

class Etat;

class Trs
{
    public:
        Etat* from;
        char tr;
        Etat* to;
        Trs(Etat* _from, char _tr, Etat* _to);
        int operator==(const Trs& right) const;
        int operator!=(const Trs& right) const;
        int operator<(const Trs& right) const;
        int operator<=(const Trs& right) const;
        int operator>(const Trs& right) const;
        int operator>=(const Trs& right) const;
        std::string get_str() const;
};

int compare_trs_pt(const Trs* a, const Trs* b);


class Etat
{
    private:
        std::vector<int> labels;
        std::vector<Etat*> old;
        bool ini;
        bool ter;
        std::vector<Trs*> prec;
        std::vector<Trs*> succ;
    public:
        int operator<(const Etat& right) const;
        int operator==(const Etat& right) const;
        Etat(std::vector<int> _labels, bool _ini, bool _ter);
        //~Etat();
        std::string get_label() const;
        std::vector<int> get_vect_label() const;
        void afficher_etat(int nb_symboles) const;
        void add_prec(Trs* _prec);
        void add_succ(Trs* _succ);
        void set_old(std::vector<Etat*> ets);
        std::vector<Etat*> get_old() const;
        std::vector<Trs*> get_succ() const;
        std::vector<Trs*> get_prec() const;
        std::vector<Trs*> get_trs(char c) const;
        void set_ter(bool _ter);
        void set_ini(bool _ini);
        bool get_ter();
        bool get_ini();
        void sort();

};

int compare_etat_pt(const Etat* a, const Etat* b);
Etat* contact_name_etat(std::vector<Etat*> ets);
std::vector<Etat*> get_old_transitions(const Etat* et, char c);
Etat* find_etat(const std::vector<Etat*>& ets, Etat* et);
Etat* epsilon_cloture(std::vector<Etat*> et);

#endif
