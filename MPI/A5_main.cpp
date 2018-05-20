#include <iostream>
#include "A5_automate.h"
using namespace std;

int main()
{
    Automate A("A5_exemple.txt");
    A.afficher_etats();
    A.afficher_transitions();
    A.afficher_table();
    
    cout << "BEGIN DETERMINISATION" << endl;
    Automate B = A.determiniser();
    B.afficher_table();
    return 0;

}
