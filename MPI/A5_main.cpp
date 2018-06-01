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
        Automate* B = aut->determinisation_completion();
        cout << i << ": " << aut->est_complet() << " " << B->est_complet() << endl;
        delete aut;
        delete B;
    }

}
