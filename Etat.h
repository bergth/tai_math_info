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
        std::vector<tr_t*> acc;
    public:
        std::string get_label();
        Etat(std::vector<int> _labels): labels(_labels) {}
        
};



#endif