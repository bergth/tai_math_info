#include <iostream>
#include <fstream>
#include "A5_execution.hpp"
#include "A5_automate.h"
using namespace std;


int main()
{
    cout << "BEGIN ##" << endl;
    /*for(int i = 1; i <= 42; i++)
    {
        traitements(i);
    }*/
    traitements(40);
    cout << "END ##" << endl;
    /*Automate* A = lire_automate(20);
    Automate* B = A->determinisation_completion();
    cout << B->to_dot() << endl;
    B->trouver_n_premiers_mots(10,6);
    delete A;
    delete B;*/
}

