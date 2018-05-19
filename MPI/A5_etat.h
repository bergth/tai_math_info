#ifndef ETAT_H
#define ETAT_H

#include<vector>
#include<string>
#include "A5_utile.h"

class Etat;

struct tr_t
{
    Etat* from;
    char tr;
    Etat* to;
};


typedef struct tr_t tr_t;


class Etat
{
    private:
        std::vector<int> labels;
        bool ini;
        bool ter;
        std::vector<tr_t*> prec;
        std::vector<tr_t*> succ;
    public:
        Etat(std::vector<int> _labels, bool _ini, bool _ter);
        std::string get_label();
        void add_prec(tr_t* _prec);
        void add_succ(tr_t* _succ);
        void set_ter(bool _ter);
        void set_ini(bool _ini);

};



#endif
