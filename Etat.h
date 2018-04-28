#ifndef ETAT_H
#define ETAT_H

#include<vector>
#include<string>

class Etat;

typedef std::tuple<Etat*, char, Etat*> tr_t;


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
        
};



#endif