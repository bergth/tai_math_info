#include <iostream>
#include "Automate.h"
using namespace std;

int main()
{
    Automate A("exemple.txt");
    A.afficher_etats();
    A.afficher_transitions();
    cout << A.to_dot();
    return 0;
}
