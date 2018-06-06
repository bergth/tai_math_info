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
        // liste de labels pour former le nom de l'état
        std::vector<int> labels;
        // liste des anciens états utilisés pour créer cet état
        std::vector<Etat*> old;
        // état initial
        bool ini;
        // état terminal
        bool ter;
        // transitions arrivant sur l'état
        std::vector<Trs*> prec;
        // transitions partant de l'état
        std::vector<Trs*> succ;
        // moded'affichage automate minimal
        bool aminimal;
    public:
        // permet de créer une relation d'ordre entre les états
        int operator<(const Etat& right) const;
        int operator==(const Etat& right) const;
        // Constructeur: liste de label, initial, terminal, affichage minimal
        Etat(std::vector<int> _labels, bool _ini, bool _ter, bool _aminimal);
        // retourne une string avec le nom de l'automate
        std::string get_label() const;
        // retourne le vecteur de labels
        std::vector<int> get_vect_label() const;
        // affiche un état
        void afficher_etat(int nb_symboles) const;
        // affiche un état pour la minimisation
        void afficher_etat_minimisation(int nb_symboles, std::vector<char> trsSousPart) const;
        // ajoute un prédécesseur à notre état
        void add_prec(Trs* _prec);
        // ajoute un successeur à notre état
        void add_succ(Trs* _succ);
        // défini le vecteur old
        void set_old(std::vector<Etat*> ets);
        // string contenant les noms de tous les anciens état
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

// permet de comparer deux états entre eux
int compare_etat_pt(const Etat* a, const Etat* b);
// retourne un nouvel état donc le nom a été concaténé avec le nom des anciens état (pour la minimisation)
Etat* contact_name_etat(std::vector<Etat*> ets);
std::vector<Etat*> get_old_transitions(const Etat* et, char c);
// trouve un état dans une liste d'état
Etat* find_etat(const std::vector<Etat*>& ets, Etat* et);
// trouve un état concaténé avec le nom de l'epsilon cloture d'un état
Etat* epsilon_cloture(std::vector<Etat*> et);

#endif
