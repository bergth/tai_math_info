#include <fstream>
#include <iostream>
#include<cstdlib>
#include "A5_automate.h"
#include "A5_utile.h"

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
    nb_symboles = u_stoi(line);
    getline(file,line);
    nb_etats = u_stoi(line);

    for(size_t i = 0; i < nb_etats; i++)
    {
        vector<int> nvec;
        nvec.push_back((int)i);
        Etat* tmp = new Etat(nvec,false,false);
        etats.push_back(tmp);
    }

    // lecture etats initiaux
    getline(file,line);
    vector<int> read = u_string_to_intvec(line);
    nb_etatsInitiaux = read[0];
    int val;
    for(size_t i = 1; i < nb_etatsInitiaux + 1; i++)
    {
        val = read[i];
        etats[val]->set_ini(true);
        etatsInitiaux.push_back(etats[val]);
    }

    // lecture etats finaux
    getline(file,line);
    read = u_string_to_intvec(line);
    nb_etatsTerminaux = read[0];
    for(size_t i = 1; i < nb_etatsTerminaux + 1; i++)
    {
        val = read[i];
        etats[val]->set_ter(true);
        etatsTerminaux.push_back(etats[val]);
    }

    // lecture nombre de transitions
    getline(file,line);
    nb_transitions = u_stoi(line);
    for(size_t j = 0; j < nb_transitions; j++)
    {
        // lecture transitions
        Etat* from = 0;
        Etat* to = 0;
        char c = 0;
        string tmp = "";
        getline(file,line);
        size_t i = 0;
        while(i < line.size() && line[i] >= '0' && line[i] <= '9')
        {
            tmp += line[i];
            i++;
        }
        from = etats[u_stoi(tmp)];
        c = line[i];
        if(i < line.size())
            i++;
        tmp = "";
        while(i < line.size() && line[i] >= '0' && line[i] <= '9')
        {
            tmp += line[i];
            i++;
        }
        to = etats[u_stoi(tmp)];
        ajouter_transition(from,c,to);
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
        cout << i << ": " << transitions[i]->from->get_label() << " -> ";
        cout << transitions[i]->tr << " -> ";
        cout << transitions[i]->to->get_label();
        cout << endl;
    }
}

Etat* Automate::ajouter_etat(vector<int> &labels, bool ini, bool ter)
{
    Etat* netat = new Etat(labels, ini, ter);
    etats.push_back(netat);
    return netat;
}

Trs* Automate::ajouter_transition(Etat* from, char c, Etat* to)
{
    Trs* tmp_tr = new Trs;
    tmp_tr->from = from;
    tmp_tr->tr = c;
    tmp_tr->to = to;
    from->add_prec(tmp_tr);
    to->add_succ(tmp_tr);



    transitions.push_back(tmp_tr);
    return tmp_tr;
}

string Automate::to_dot()
{
    vector<Trs*>::iterator it;
    string str = "digraph G {\n";
    string init = "";
    string trans = "";
    for(it = transitions.begin(); it != transitions.end(); it++)
    {
        string name_from = (*it)->from->get_label();
        char c = (*it)->tr;
        string name_to = (*it)->to->get_label();
        string line = "    \"";
        line += name_from;
        line += "\" -> \"";
        line += name_to;
        line += "\" [ label=\"";
        line += c;
        line += "\"];\n";
        trans += line;
    }

    vector<Etat*>::iterator eit;
    int i = 0;
    for(eit = etatsInitiaux.begin(); eit != etatsInitiaux.end(); eit++)
    {
        init  +=    "    node [shape = point, color = white, fontcolor = white]; start" + u_to_string(i) + ";\n";
        trans +=    "    start" + u_to_string(i) + " -> \"" + (*eit)->get_label() + "\";\n";
        i++;
    }

    i = 0;
    for(eit = etatsTerminaux.begin(); eit != etatsTerminaux.end(); eit++)
    {
        init  +=    "    node [shape = point, color = white, fontcolor = white]; end" + u_to_string(i) + ";\n";
        trans +=    "   \"" + (*eit)->get_label() + "\" ->  end" + u_to_string(i) + " ;\n";
        i++;
    }

    init += "    node [shape = circle, color = black, fontcolor = black];\n";
    str += init;
    str += trans;
    str += "}\n";
    return str;
}
/*
void strandardisation()
{
    vector<Trs*>::iterator it;
    vector<Etat*>::iterator eit;
    bool tr_vers_entree = false; //si des transitions reviennent vers l'entree
    bool entree_ter = false; //si au moins une entree est terminale
    for(eit = etatsInitiaux.begin(); eit != etatsInitiaux.end(); eit++)
    {
        if(**eit.init == true) entree_ter = true;
        for(it = transitions.begin(); it != transitions.end(); it++)
        {
            if(get<0>(**it) == (**eit)) tr_vers_entree == false;
        }

    }

    if(nb_etatsInitiaux > 1 || tr_entree == true) // condition pour non-standardise
    {
        if(entree_ter == true) // Si l'automate reconnait le mot vide
            Etat *init = ajouter_etat(, true, true);
        else Etat *init = ajouter_etat(, true, false);

        for(eit = etatsInitiaux.begin(); eit != etatsInitiaux.end(); eit++)
        {
            **eit.init = false;

            //Il faut relier le nouvel etat initial aux anciens. Je ne sais pas comment faire.
        }

        etatsInitiaux.erase(etatsInitiaux.begin(), etatsInitiaux.end());
        etatInitiaux[0] = *init;


    }
}
*/
