#ifndef AUTOMATE_H_INCLUDED
#define AUTOMATE_H_INCLUDED

class Automate
{
    private:
        // Directement dérivé du cours : définition d'un automate
        std::vector<Etat*> etats;
        std::vector<Etat*> etatsInitiaux;
        std::vector<Etat*> etatsTerminaux;
        std::vector<std::tuple<Etat*, Lettre, Etat*>> transitions; // OU : encapsuler les transitions en définissant une classe Transition

    public:
        // Constructeur prend en paramètre le fichier contenant les données de l'automate à construire
        Automate(const char* file);
        ~Automate();
};

#endif // AUTOMATE_H_INCLUDED
