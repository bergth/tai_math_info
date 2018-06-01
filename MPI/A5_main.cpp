#include <iostream>
#include<cstdlib>

#include "A5_automate.h"
using namespace std;

Automate lire_automate(size_t n)
{
    if(n <= 0 || n > 42)
    {
        cerr << "Erreur: automate doit être compris entre 1 et 42" << endl;
        exit(1);
    }
    string prefix = "A5_";
    string suffix = ".txt";
    string name = u_to_nstring(n,2);
    return Automate((prefix+name+suffix).c_str());
}


int main()
{
    /*Automate A("A5_42.txt");
    cout << "##############" << endl;
    A.afficher_table();
    cout << "##############" << endl;
    cout << A.to_dot() << endl;*/
    cout << "BEGIN ##" << endl;
    for(size_t i = 1; i <= 42; i++)
    {
        Automate aut = lire_automate(i);
        cout << i << ": " << aut.est_complet() << endl;
    }
    cout << "END ##" << endl;

    Automate A = lire_automate(18);
    A.afficher_table();

    /*cout << "BEGIN DETERMINISATION" << endl;*/
    //Automate B = A.determiniser(true);
    //Automate C = B.determiniser(false);
    //cout << B.to_dot() << endl;
    //cout << C.to_dot() << endl;
    //Automate B = A.determiniser();
    //cout << B.to_dot() << endl;
    //cout << "BEGIN COMPLETION" << endl;
    //Automate C = B.completer();
    //cout << C.to_dot() << endl;
    //cout << B.est_complet() << endl;
    //cout << C.est_complet() << endl;
    //cout << B.reconnaitre_mot("bbbccd") << endl;
    //return 0;
}
