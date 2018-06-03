#include<iostream>
#include<cstdlib>

#include "A5_execution.hpp"

using namespace std;

Automate* lire_automate(size_t n)
{
    if(n <= 0 || n > 42)
    {
        cerr << "Erreur: automate doit être compris entre 1 et 42" << endl;
        exit(1);
    }
    string prefix = "A5_";
    string suffix = ".txt";
    string name = u_to_nstring(n,2);
    return new Automate((prefix+name+suffix).c_str());
}

string lire_mot()
{
    char val[256];
    cout << "[saisir mot (256 max) ]> ";
    cin.getline(val,256);
    string ns(val);
    return ns;
}

void reconnaissance_de_mots(const Automate* A)
{
    cout << "Reconnaissance de mots" << endl;
    cout << "Saisir une série de mots" << endl;
    cout << "'fin' pour arrêter" << endl;
    cout << "retour à la ligne pour mot vide" << endl;
    string mot = lire_mot();
    while(mot != "fin")
    {
        if(A->reconnaitre_mot(mot))
            cout << "Mot reconnu" << endl;
        else
            cout << "Mot non reconnu" << endl;
        mot = lire_mot();
    }
}

void language_complementaire(const Automate* A)
{
    const Automate* aut;
    Automate* comp;
    if(A->est_complet())
    {
        aut = A;
    }
    else
    {
        aut = A->completer();
    }
    comp = aut->complementariser();
    comp->afficher_table();
    reconnaissance_de_mots(comp);
    if(!(A->est_complet()))
        delete aut;
    delete comp;
}