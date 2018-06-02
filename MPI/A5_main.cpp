#include <iostream>
#include <fstream>
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
        Automate* B = aut->standardiser();
        string a = "../tests_determinisation/"+u_to_nstring(i,2)+"_nd.txt";
        string b = "../tests_determinisation/"+u_to_nstring(i,2)+"_d.txt";
        std::ofstream out_nd(a.c_str());
        std::ofstream out_d(b.c_str());
        out_nd << aut->to_dot();
        out_d << B->to_dot();
        out_nd.close();
        out_d.close();
        delete aut;
        delete B;
    } 
    cout << "END ##" << endl;
    /*Automate* A = lire_automate(20);
    Automate* B = A->determinisation_completion();
    cout << B->to_dot() << endl;
    B->trouver_n_premiers_mots(10,6);
    delete A;
    delete B;*/
}

