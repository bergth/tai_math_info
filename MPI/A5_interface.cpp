#include "A5_interface.hpp"
#include "A5_execution.hpp"
#include "A5_utile.h"
#include <iostream>

using namespace std;

Interface::Interface()
{
    nb = 0;
    str = "";
}


Interface::~Interface()
{
    clear();
}

void Interface::start()
{
    str = "";
    while(true)
    {
        cout << "[" << nb << "]> "; 
        getline(cin,str);
        //cout << "[[" << str << "]]" << endl;
        if(str == "quitter" || str == "q")
        {
            break;
        }
        traitement();
    }
}

void Interface::lister_automates()
{
    for(size_t i = 0; i < nb; i++)
    {
        cout << "[" << i << "]" << " <-- " << orgs[i] << endl;
    }
}

void Interface::traitement()
{
    vector<string> strs = string_to_strvec(str);
    //cout << "[" << strs[0] << "]" << endl;
    if(strs[0] == "vider")
    {
        clear();
    }
    else if (strs[0] == "lister")
    {
        lister_automates();
    }
    else if(strs[0] == "lire")
    {
        if(strs.size() != 2)
            cout << "Erreur commande: rentrer numéro automate" << endl;
        else
        {
            int n = u_stoi(strs[1]);
            if(n >= 1 && n <= 42)
            {
                orgs.push_back(str);
                auts.push_back(lire_automate(u_stoi(strs[1])));
                nb++;
            }
            else
            {
                cout << "Rentrer nombre entre 1 et 42 inclus" << endl;
            }
        }
    }
    else
    {
        size_t n;
        if(strs.size() == 0)
            cout << "Command vide" << endl;
        else if(strs.size() == 1)
        {
            if(nb == 0)
            {
                cout << "Il n'y a pas encore d'automate" << endl;
                return;
            }
            n = nb - 1;
        }
        else if(strs.size() == 2)
        {
            n = u_stoi(strs[1]);
            if(n >= auts.size())
            {
                cout << "Erreur commante: mauvais numéros de liste" << endl;
                return;
            }
        }
        else
        {
            cout << "Erreur commande: rentrer numéro automate dans la liste (cf lister)" << endl;
            return;
        }


        if(strs[0] == "afficher")
        {
            auts[n]->afficher_table();
        }
        else if(strs[0] == "determiniser")
        {
            auts.push_back(auts[n]->determinisation_completion());
            orgs.push_back(str);
            nb++;
        }
        else if(strs[0] == "minimiser")
        {

    
        }
        else if(strs[0] == "reconnaitre")
        {
            reconnaissance_de_mots(auts[n]);
        }
        else if(strs[0] == "traitements")
        {
            traitements(auts[n]);
        }
        else if(strs[0] == "estDeterministe")
            auts[n]->est_deterministe();
        else if(strs[0] == "estAsynchrone")
            auts[n]->est_asynchrone();
        else if(strs[0] == "estDComplet")
            auts[n]->est_deterministe_complet();
        else
        {
        cout << "Commande inconnue" << endl;
        }
    }
}

void Interface::clear()
{
    for(size_t i = 0; i < auts.size(); i++)
    {
        delete auts[i];
    }
    auts.clear();
    orgs.clear();
    nb = 0;
}