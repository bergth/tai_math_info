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
    /*for(size_t i = 1; i <= 42; i++)
    {
        Automate* aut = lire_automate(i);
        cout << i << " aut: " << aut->est_complet() << " d? " << aut->est_deterministe() << endl;
        Automate* B = aut->determinisation_completion();
        cout << i << " B: " << B->est_complet() << " d? " << B->est_deterministe() << endl;
        delete aut;
        delete B;
    }*/
    Automate* A = lire_automate(42);
    cout << A->est_deterministe() << endl;
    Automate* B = A->determinisation_completion();
    cout << B->est_deterministe() << endl;
    delete A;
    delete B;
    cout << "END ##" << endl;

}
