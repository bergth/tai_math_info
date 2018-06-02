#include <iostream>
#include<cstdlib>

#include "A5_automate.h"
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


int main()
{
    cout << "BEGIN ##" << endl;
    for(size_t i = 1; i <= 42; i++)
    {
        Automate* aut = lire_automate(i);
        cout << i << ": ";
        aut->trouver_n_premiers_mots(15,6);
        delete aut;
    } 
    /*Automate* A = lire_automate(20);
    Automate* B = A->determinisation_completion();
    cout << B->to_dot() << endl;
    B->trouver_n_premiers_mots(10,6);
    delete A;
    delete B;*/
}

