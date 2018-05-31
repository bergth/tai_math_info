#include <iostream>
#include "A5_automate.h"
using namespace std;

int main()
{
    Automate A("A5_31.txt");
    cout << A.to_dot() << endl;
    cout << "BEGIN DETERMINISATION" << endl;
    Automate B = A.determiniser(true);
    Automate C = B.determiniser(false);
    cout << B.to_dot() << endl;
    cout << C.to_dot() << endl;
    //Automate B = A.determiniser();
    //cout << B.to_dot() << endl;
    //cout << "BEGIN COMPLETION" << endl;
    //Automate C = B.completer();
    //cout << C.to_dot() << endl;
    //cout << B.est_complet() << endl;
    //cout << C.est_complet() << endl;
    //cout << B.reconnaitre_mot("bbbccd") << endl;
    return 0;
}
