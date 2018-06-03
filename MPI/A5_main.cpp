#include <iostream>
#include <fstream>
#include "A5_execution.hpp"
#include "A5_automate.h"
using namespace std;


int main()
{
    cout << "BEGIN ##" << endl;
    Automate* aut = lire_automate(40);
    aut->afficher_table();
    //reconnaissance_de_mots(aut);
    //language_complementaire(aut);
    Automate* B = aut->determinisation_completion();
    B->afficher_table();
    delete aut;
    delete B;
    /*for(size_t i = 1; i <= 42; i++)
    {
        Automate* aut = lire_automate(i);
        Automate* B = aut->determinisation_completion();
        Automate* C = B->complementariser();
        string a = "../tests_determinisation/"+u_to_nstring(i,2)+"_nd.txt";
        string b = "../tests_determinisation/"+u_to_nstring(i,2)+"_d.txt";
        std::ofstream out_nd(a.c_str());
        std::ofstream out_d(b.c_str());
        out_nd << B->to_dot();
        out_d << C->to_dot();
        out_nd.close();
        out_d.close();
        delete aut;
        delete B;
        delete C;
    } */
    cout << "END ##" << endl;
    /*Automate* A = lire_automate(20);
    Automate* B = A->determinisation_completion();
    cout << B->to_dot() << endl;
    B->trouver_n_premiers_mots(10,6);
    delete A;
    delete B;*/
}

