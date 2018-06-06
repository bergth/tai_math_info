#include "A5_ensemble.h"

using namespace std;

Ensemble::Ensemble(int addLabel)
{
    label = 'A' + ((char)addLabel);
}

Ensemble::Ensemble(const Ensemble& copie, int addLabel)
{
    label = 'A' + ((char)addLabel);
    for (unsigned int i(0); i < copie.vecEtats.size(); i++)
    {
        vecEtats.push_back(copie.vecEtats[i]);
    }
}

Ensemble::~Ensemble()
{
    while (vecEtats.size() > 0)
    {
        vecEtats.pop_back();
    }
}

// Ajouter un état à l'ensemble
void Ensemble::ajouterEtat(Etat* etat)
{
    // On rajoute l'état au vecteur d'états de l'ensemble
    vecEtats.push_back(etat);
}

int Ensemble::getSize() const
{
    return vecEtats.size();
}

vector<Etat*> Ensemble::getVecEtats() const
{
    return vecEtats;
}

char Ensemble::getLabel() const
{
    return label;
}
