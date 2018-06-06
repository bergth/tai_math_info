#ifndef AUTOMATE_H_INCLUDED
#define AUTOMATE_H_INCLUDED
#include <vector>
#include "A5_etat.h"





class Automate
{


    private:
        // Nombres de symboles
        size_t nb_symboles;
        // Nombres d'états
        size_t nb_etats;
        // vecteur d'états
        std::vector<Etat*> etats;
        // nombre d'états initiaux
        size_t nb_etatsInitiaux;
        // liste d'états initiaux
        std::vector<Etat*> etatsInitiaux;
        // nombre d'états terminaux
        size_t nb_etatsTerminaux;
        // liste d'états terminaux
        std::vector<Etat*> etatsTerminaux;
        // nombre de transitions
        size_t nb_transitions;
        // liste de transitions
        std::vector<Trs*> transitions;
        // Fonctions lectures de fichier
        Trs* lire_transition(std::string str);
        Trs* lire_grp_etats(std::string str);
        // permet d'ajouter un état à l'automate
        Etat* ajouter_etat(std::vector<int> &labels, bool ini, bool ter);
        // permet d'ajouter une transition à l'automate
        Trs* ajouter_transition(Etat* from, char c, Etat* to);
        bool affichage_minimal;
    public:
        // Constructeur prend en paramètre le fichier contenant les données de l'automate à construire
        Automate(const char* file);
        // Constructeur prend en paramètre un nombre de symboles, une liste d'états et de transition pour construire un automate
        Automate(size_t _nb_symboles, std::vector<Etat*> _etats, std::vector<Trs*> _trs,bool _aminimal);
        // destructeur
        ~Automate();
        // afficher une liste d'état
        void afficher_etats();
        // afficher une liste de transitions
        void afficher_transitions();
        // afficher la table de transition
        void afficher_table() const;
        // retourner la syntax graphviz
        std::string to_dot();
        // permet de trier les états et les transitions
        void sort();
        // test si un automate est asynchrone
        bool est_asynchrone() const;
        // test si un automate est déterministe
        bool est_deterministe() const;
        // déterminise et complete un zutomate
        Automate* determinisation_completion() const;
        // déterminise un automate asynchrone ou non
        Automate* determiniser(bool asynchrone) const;
        // test si un automate est déterministe et complet
        bool est_deterministe_complet() const;
        // minimise l'automate
        Automate* minimisation();
        // test si un automate est standard
        bool est_Standard() const;
        // complete un automate
        Automate* completer() const;
        // standardise un automate
        Automate* standardiser() const;
        // retourne si un mot est reconnu par l'automate ou non
        bool reconnaitre_mot(std::string mot) const;
        // trouve les n premières occurences de mots de taille max l reconnus par l'automate
        void trouver_n_premiers_mots(size_t n, size_t l);
        // copie un automate
        Automate* copier() const;
        // copie les états, transitions d'un automate
        void copier_et_trs(std::vector<Etat*> &vect_etats, std::vector<Trs*> &transi) const;
        // complémentatire un automate
        Automate* complementariser() const;

};

#endif // AUTOMATE_H_INCLUDED
