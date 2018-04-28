#ifndef AUTOMATE_H_INCLUDED
#define AUTOMATE_H_INCLUDED
#include <vector>
#include "Etat.h"

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
        std::vector<tr_t*> transitions;
        // Fonctions lectures de fichier
        tr_t* lire_transition(std::string str);
        tr_t* lire_grp_etats(std::string str);
        Etat* ajouter_etat(std::vector<int> &labels, bool ini, bool ter);
        tr_t* ajouter_transition(Etat* from, char c, Etat* to);

    public:
        // Constructeur prend en paramètre le fichier contenant les données de l'automate à construire
        Automate(const char* file);
        ~Automate();
        void afficher_etats();
        void afficher_transitions();
        std::string to_dot();
};

#endif // AUTOMATE_H_INCLUDED