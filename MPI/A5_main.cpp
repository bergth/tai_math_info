#include <iostream>
#include <fstream>
#include "A5_execution.hpp"
#include "A5_automate.h"
using namespace std;


int main()
{
    cout << "BEGIN ##" << endl;
    /*for(int i = 13; i < 42; i++)
    {
        cout << i << endl;
        Automate* A = lire_automate(i);
        Automate* B = A->determinisation_completion();
        cout << "determinisation" << endl;
        B->trouver_n_premiers_mots(10,6);
        Automate* C = B->minimiser();
        cout << "minimisation" << endl;
        C->trouver_n_premiers_mots(10,6);
       // Automate* D = C->complementariser();
        //D->trouver_n_premiers_mots(10,6);
        delete A;
        delete B;
        delete C;
      //  delete D;
        traitements(i);
    }*/
    traitements(26);
    cout << "END ##" << endl;
    /*Automate* A = lire_automate(20);
    Automate* B = A->determinisation_completion();
    cout << B->to_dot() << endl;
    B->trouver_n_premiers_mots(10,6);
    delete A;
    delete B;*/
}

