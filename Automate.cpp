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

    for(size_t i = 0; i < nb_etats; i++)
    {
        Etat* tmp = new Etat({(int)i},false,false);
        etats.push_back(tmp);
    }

    // lecture etats initiaux
    getline(file,line);
    vector<int> read = string_to_intvec(line);
    nb_etatsInitiaux = read[0];
    int val;
    for(size_t i = 1; i < nb_etatsInitiaux + 1; i++)
    {
        val = read[i];
        etatsInitiaux.push_back(etats[val]);
    }
    
    // lecture etats finaux
    getline(file,line);
    read = string_to_intvec(line);
    nb_etatsTerminaux = read[0];
    for(size_t i = 1; i < nb_etatsTerminaux + 1; i++)
    {
        val = read[i];
        etatsTerminaux.push_back(etats[val]);
    }

    // lecture nombre de transitions
    getline(file,line);
    nb_transitions = stoi(line);
    for(size_t j = 0; j < nb_transitions; j++)
    {
        // lecture transitions
        tr_t* tmp_tr = new tr_t;
        string tmp = "";
        getline(file,line);
        size_t i = 0;
        while(i < line.size() && line[i] >= '0' && line[i] <= '9')
        {
            tmp += line[i];
            i++;
        }
        get<0>(*tmp_tr) = etats[stoi(tmp)];
        get<1>(*tmp_tr) = line[i];
        if(i < line.size())
            i++;
        tmp = "";
        while(i < line.size() && line[i] >= '0' && line[i] <= '9')
        {
            tmp += line[i];
            i++;
        }
        get<2>(*tmp_tr) = etats[stoi(tmp)];
        transitions.push_back(tmp_tr);
    }
}

Automate::~Automate()
{
    for(size_t i = 0; i < etats.size(); i++)
    {
        delete etats[i];
    }

    for(size_t i = 0; i < transitions.size(); i++)
    {
        delete transitions[i];
    }
}

void Automate::afficher_etats()
{
    cout << "Nombre d'états: " << nb_etats << endl;
    for(size_t i = 0; i < nb_etats; i++)
    {
        cout << i << ": " << etats[i]->get_label() << endl;
    }
}

void Automate::afficher_transitions()
{
    cout << "Nombre de transition: " << nb_transitions << endl;
    for(size_t i = 0; i < nb_transitions; i++)
    {
        cout << i << ": " << (get<0>(*transitions[i]))->get_label() << " -> ";
        cout << get<1>(*transitions[i]) << " -> ";
        cout << (get<2>(*transitions[i]))->get_label();
        cout << endl;
    } 
}

Etat* Automate::ajouter_etat(vector<int> &labels, bool ini, bool ter)
{
    Etat* netat = new Etat(labels, ini, ter);
    etats.push_back(netat);
    return netat;
}