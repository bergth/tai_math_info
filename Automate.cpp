#include <fstream>
#include <iostream>
#include <tuple>
#include "Automate.h"
#include "utile.h"

using namespace std;


Automate::Automate(const char* fname)
{
    std::ifstream file(fname);
    if(!file)
    {
        cerr << "Erreur ouverture fichier (initialisation)" << endl;
        exit(1);
    }

    string line;
    // lecture symboles et etats
    getline(file,line);
    nb_symboles = stoi(line,nullptr,10);
    getline(file,line);
    nb_etats = stoi(line,nullptr,10);

    for(int i = 0; i < nb_etats; i++)
    {
        Etat* tmp = new Etat({i});
        etats.push_back(tmp);
    }

    // lecture etats initiaux et terminaux
    tuple<int,int,int> tup;
    getline(file,line);
    tup = string_to_tupple(line);
    

}

Automate::~Automate()
{

}
