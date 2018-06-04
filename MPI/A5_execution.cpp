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
    if(A->est_deterministe_complet())
    {
        aut = A;
    }
    else
    {
        aut = A->completer();
    }
    comp = aut->complementariser();
    //comp->afficher_table();
    reconnaissance_de_mots(comp);
    if(!(A->est_deterministe_complet()))
        delete aut;
    delete comp;
}

void traitements(size_t n)
{
    Automate* A = lire_automate(n);
    cout << "[AF]#########################" << endl << endl;
    A->afficher_table();
    Automate* B = A->determinisation_completion();
    cout << "[AFDC]#########################" << endl << endl;
    B->afficher_table();
    Automate* X = B->minimiser();
    cout << "[AFDCM]#########################" << endl << endl;
    X->afficher_table();
    Automate* C = X->complementariser();
    cout << "[AComp]#########################" << endl << endl;
    C->afficher_table();
    Automate* D = C->standardiser();
    cout << "[ACompStd]#########################" << endl << endl;
    D->afficher_table();
    reconnaissance_de_mots(X);
    language_complementaire(X);
    cout << X->to_dot() << endl;
    delete A;
    delete B;
    delete C;
    delete D;
    delete X;
    //delete D;
}