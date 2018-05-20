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
        int operator==(const Trs& right) const;
        int operator!=(const Trs& right) const;
        int operator<(const Trs& right) const;
        int operator<=(const Trs& right) const;
        int operator>(const Trs& right) const;
        int operator>=(const Trs& right) const;
};


class Etat
{
    private:
        std::vector<int> labels;
        bool ini;
        bool ter;
        std::vector<Trs*> prec;
        std::vector<Trs*> succ;
    public:
        Etat(std::vector<int> _labels, bool _ini, bool _ter);
        std::string get_label();
        std::vector<int> get_vect_label();
        void afficher_etat();
        void add_prec(Trs* _prec);
        void add_succ(Trs* _succ);
        void set_ter(bool _ter);
        void set_ini(bool _ini);
        
};



#endif
