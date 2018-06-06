#ifndef A5_ENSEMBLE_H_INCLUDED
#define A5_ENSEMBLE_H_INCLUDED

#include <vector>
#include "A5_etat.h"

class Ensemble
{
    private:
        // Le nom de l'ensemble
        char label;
        // Un tableau dynamique contenant les états composant l'ensemble
        std::vector<Etat*> vecEtats;
    public:
        Ensemble(int addLabel);
        ~Ensemble();
        Ensemble(const Ensemble& copie, int addLabel);
        void ajouterEtat(Etat* etat);
        int getSize() const;
        std::vector<Etat*> getVecEtats() const;
        char getLabel() const;
};

#endif // A5_ENSEMBLE_H_INCLUDED
