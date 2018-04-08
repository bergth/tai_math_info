#ifndef AUTOMATE_H_INCLUDED
#define AUTOMATE_H_INCLUDED

class Automate
{
    private:
        // Directement d�riv� du cours : d�finition d'un automate
        std::vector<Etat*> etats;
        std::vector<Etat*> etatsInitiaux;
        std::vector<Etat*> etatsTerminaux;
        std::vector<std::tuple<Etat*, Lettre, Etat*>> transitions; // OU : encapsuler les transitions en d�finissant une classe Transition

    public:
        // Constructeur prend en param�tre le fichier contenant les donn�es de l'automate � construire
        Automate(const char* file);
        ~Automate();
};

#endif // AUTOMATE_H_INCLUDED
