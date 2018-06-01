#ifndef AUTOMATE_H_INCLUDED
#define AUTOMATE_H_INCLUDED
#include <vector>
#include "A5_etat.h"

class Automate
{


    private:
        // Directement dérivé du cours : définition d'un automate
        size_t nb_symboles;
        size_t nb_etats;
        std::vector<Etat*> etats;
        size_t nb_etatsInitiaux;
        std::vector<Etat*> etatsInitiaux;
        size_t nb_etatsTerminaux;
        std::vector<Etat*> etatsTerminaux;
        size_t nb_transitions;
        std::vector<Trs*> transitions;
        // Fonctions lectures de fichier
        Trs* lire_transition(std::string str);
        Trs* lire_grp_etats(std::string str);
        Etat* ajouter_etat(std::vector<int> &labels, bool ini, bool ter);
        Trs* ajouter_transition(Etat* from, char c, Etat* to);
    public:
        // Constructeur prend en paramètre le fichier contenant les données de l'automate à construire
        Automate(const char* file);
        Automate(size_t _nb_symboles, std::vector<Etat*> _etats, std::vector<Trs*> _trs);
        ~Automate();
        void afficher_etats();
        void afficher_transitions();
        void afficher_table() const;
        std::string to_dot();
        void sort();
        bool est_synchrone() const;
        bool est_deterministe() const;
        Automate* determinisation_completion() const;
        Automate* determiniser(bool asynchrone) const;
        Automate* determiniser_asynchrone() const;
        bool est_complet() const;
        Automate* completer() const;
        bool reconnaitre_mot(std::string mot);
        Automate* copier() const;

};

#endif // AUTOMATE_H_INCLUDED
