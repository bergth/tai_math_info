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
    help();
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
    if(strs[0] == "help")
    {
        help();
        return;
    }
    if(strs[0] == "vider")
    {
        clear();
        return;
    }
    else if (strs[0] == "lister" || strs[0] == "lst")
    {
        lister_automates();
        return;
    }
    else if(strs[0] == "lire" || strs[0] == "l")
    {
        if(strs.size() != 2)
            cout << "Erreur commande: rentrer numero automate" << endl;
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


        if(strs[0] == "afficher" || strs[0] == "a")
        {
            auts[n]->afficher_table();
        }
        else if(strs[0] == "determiniser" || strs[0] == "d")
        {
            auts.push_back(auts[n]->determinisation_completion());
            orgs.push_back(str);
            nb++;
        }
        else if(strs[0] == "completer" || strs[0] == "c")
        {
            auts.push_back(auts[n]->completer());
            orgs.push_back(str);
            nb++;
        }
        else if(strs[0] == "minimiser" || strs[0] == "m")
        {
            auts.push_back(auts[n]->minimisation());
            orgs.push_back(str);
            nb++;
        }
        else if(strs[0] == "complementer" || strs[0] == "cm")
        {
            auts.push_back(auts[n]->complementariser());
            orgs.push_back(str);
            nb++;
        }
        else if(strs[0] == "standardiser" || strs[0] == "std")
        {
            auts.push_back(auts[n]->standardiser());
            orgs.push_back(str);
            nb++;
        }
        else if(strs[0] == "reconnaitre" || strs[0] == "r")
        {
            reconnaissance_de_mots(auts[n]);
        }
        else if(strs[0] == "traitements" || strs[0] == "tr")
        {
            traitements(auts[n]);
        }
        else if(strs[0] == "estdeterministe" || strs[0] == "ed")
            auts[n]->est_deterministe();
        else if(strs[0] == "estasynchrone" || strs[0] == "ea")
            auts[n]->est_asynchrone();
        else if(strs[0] == "estdcomplet" || strs[0] == "edc")
            auts[n]->est_deterministe_complet();
        else if(strs[0] == "eststandard" || strs[0] == "es")
            auts[n]->est_Standard();
        else if(strs[0] == "ReconnaitreComp" || strs[0] == "rc")
        {
            language_complementaire(auts[n]);
        }
        else if(strs[0] == "testerStand" || strs[0] == "ts")
        {
            test_standard(auts[n]);
        }
        else if(strs[0] == "dot")
        {
            cout << "---------------------" << endl;
            cout << auts[n]->to_dot();
            cout << "---------------------" << endl;
        }
        else if(strs[0] == "ListerMots" || strs[0] == "lm")
        {
            auts[n]->trouver_n_premiers_mots(10,6);
        }
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

void Interface::help()
{
    cout << "Liste des commandes: " << endl;
    cout << "   - help: Affiche cette aide" << endl;
    cout << "   - Quitter: quitte le programme" << endl;
    cout << "   - vider: vider la liste d'automates" << endl;
    cout << "   - LiSTer: afficher la liste d'automates" << endl;
    cout << "   - Lire A: Lire un automate. A compris entre 1 et 42" << endl;
    cout << "[n]: contient le numeros de l'automate. Si non présent: [n] = dernier automate" << endl;
    cout << "   - Afficher [n]: Affiche la table de transition" << endl;
    cout << "   - Determiniser [n]: Cree un nouvel automate deterministe" << endl;
    cout << "   - Minimiser [n]: Cree un nouvel automate  minimal" << endl;
    cout << "   - CompleMenter [n]: Cree un nouvel automate complementaire" << endl;
    cout << "   - STanDardiser [n]: Cree un nouvel automate standard" << endl;
    cout << "   - Reconnaitre [n]: Lance un test de reconnaissance de mots" << endl;
    cout << "   - ReconnaitreComp [n]: Lance un test de reconnaissance de mots sur l'automate complementaire" << endl;
    cout << "   - TRaitements [n]: Lance les traitements suivant: AF -> AFDC -> AFDCM -> Acomp -> AcompStd" << endl;
    cout << "   - EstDeterministe [n]: Test si l'automate est deterministe" << endl;
    cout << "   - EstAsynchrone [n]: Test si l'automate est Asynchrone" << endl;
    cout << "   - EstDComplet [n]: Test si l'automate est deterministre et complet" << endl;
}