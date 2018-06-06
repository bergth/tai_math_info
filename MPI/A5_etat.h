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
        std::string get_str_minimisation(const char c) const;
};

int compare_trs_pt(const Trs* a, const Trs* b);


class Etat
{
    private:
        // liste de labels pour former le nom de l'�tat
        std::vector<int> labels;
        // liste des anciens �tats utilis�s pour cr�er cet �tat
        std::vector<Etat*> old;
        // �tat initial
        bool ini;
        // �tat terminal
        bool ter;
        // transitions arrivant sur l'�tat
        std::vector<Trs*> prec;
        // transitions partant de l'�tat
        std::vector<Trs*> succ;
        // moded'affichage automate minimal
        bool aminimal;
    public:
        // permet de cr�er une relation d'ordre entre les �tats
        int operator<(const Etat& right) const;
        int operator==(const Etat& right) const;
        // Constructeur: liste de label, initial, terminal, affichage minimal
        Etat(std::vector<int> _labels, bool _ini, bool _ter, bool _aminimal);
        // retourne une string avec le nom de l'automate
        std::string get_label() const;
        // retourne le vecteur de labels
        std::vector<int> get_vect_label() const;
        // affiche un �tat
        void afficher_etat(int nb_symboles) const;
        // affiche un �tat pour la minimisation
        void afficher_etat_minimisation(int nb_symboles, std::vector<char> trsSousPart) const;
        // ajoute un pr�d�cesseur � notre �tat
        void add_prec(Trs* _prec);
        // ajoute un successeur � notre �tat
        void add_succ(Trs* _succ);
        // d�fini le vecteur old
        void set_old(std::vector<Etat*> ets);
        // string contenant les noms de tous les anciens �tat
        std::string get_name_old();
        // getters
        std::vector<Etat*> get_old() const;
        std::vector<Trs*> get_succ() const;
        std::vector<Trs*> get_prec() const;
        std::vector<Trs*> get_trs(char c) const;
        // setters
        void set_ter(bool _ter);
        void set_ini(bool _ini);
        // getters
        bool get_ter();
        bool get_ini();
        // permet de trier les listes de transitions
        void sort();

};

// permet de comparer deux �tats entre eux
int compare_etat_pt(const Etat* a, const Etat* b);
// retourne un nouvel �tat donc le nom a �t� concat�n� avec le nom des anciens �tat (pour la minimisation)
Etat* contact_name_etat(std::vector<Etat*> ets);
std::vector<Etat*> get_old_transitions(const Etat* et, char c);
// trouve un �tat dans une liste d'�tat
Etat* find_etat(const std::vector<Etat*>& ets, Etat* et);
// trouve un �tat concat�n� avec le nom de l'epsilon cloture d'un �tat
Etat* epsilon_cloture(std::vector<Etat*> et);

#endif
