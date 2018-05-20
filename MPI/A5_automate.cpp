#include <fstream>
#include <iostream>
#include<cstdlib>
#include<algorithm>
#include<queue>
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
    cout << "nombre etat:" << nb_etats << endl;
    for(size_t i = 0; i < nb_etats; i++)
    {
        vector<int> nvec;
        nvec.push_back((int)(i));
        Etat* tmp = new Etat(nvec,false,false);
        etats.push_back(tmp);
    }

    // lecture etats initiaux
    getline(file,line);
    cout << line << endl;
    vector<int> read = u_string_to_intvec(line);
    nb_etatsInitiaux = read[0];
    int val;
    cout << "read: " << read.size() << endl;
    for(size_t i = 1; i < nb_etatsInitiaux + 1; i++)
    {
        cout << i << endl;
        val = read[i];
        etats[val]->set_ini(true);
        etatsInitiaux.push_back(etats[val]);
    }

    // lecture etats finaux
    getline(file,line);
    cout << line << endl;
    read = u_string_to_intvec(line);
    nb_etatsTerminaux = read[0];
    for(size_t i = 1; i < nb_etatsTerminaux + 1; i++)
    {
        val = read[i];
        etats[val]->set_ter(true);
        etatsTerminaux.push_back(etats[val - 1]);
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
        while(line[i] == ' ')
            i++;
        while(i < line.size() && line[i] >= '0' && line[i] <= '9')
        {
            tmp += line[i];
            i++;
        }
        from = etats[u_stoi(tmp)];
        while(line[i] == ' ')
            i++;
        c = line[i];
        if(i < line.size())
            i++;
        tmp = "";
        while(line[i] == ' ')
            i++;
        while(i < line.size() && line[i] >= '0' && line[i] <= '9')
        {
            tmp += line[i];
            i++;
        }
        cout << line << endl;
        cout << "[" <<tmp << "]" << endl;
        to = etats[u_stoi(tmp)];
        ajouter_transition(from,c,to);
    }
   Automate::sort();
}

Automate::Automate(size_t _nb_symboles, std::vector<Etat*> _etats, std::vector<Trs*> _trs)
{
    nb_symboles = _nb_symboles;
    nb_etats = _etats.size();
    etats = _etats;
    nb_transitions = _trs.size();
    transitions = _trs;


    for(size_t i = 0; i < _etats.size(); i++)
    {
        if(_etats[i]->get_ini())
        {
            etatsInitiaux.push_back(_etats[i]);
            nb_etatsInitiaux++;
        }
        if(_etats[i]->get_ter())
        {
            etatsTerminaux.push_back(_etats[i]);
            nb_etatsTerminaux++;
        }
    }
    Automate::sort();
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
        cout << i << ": ";
        transitions[i]->afficher();
    }
}

void Automate::afficher_table() const
{
    for(size_t i = 0; i < nb_etats; i++)
    {
        etats[i]->afficher_etat();
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
    Trs* tmp_tr = new Trs(from,c,to);
    to->add_prec(tmp_tr);
    from->add_succ(tmp_tr);

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

void Automate::sort()
{
    for(size_t i = 0; i < etats.size(); i++)
    {
        etats[i]->sort();
    }
    std::sort(transitions.begin(),transitions.end(),compare_trs_pt);
    std::sort(etats.begin(),etats.end(),compare_etat_pt);
}


Automate Automate::determiniser() const
{
    vector<Etat*> netats;
    queue<Etat*> q;
    vector<Trs*> ntrs;
    Etat* net = contact_name_etat(etatsInitiaux);
    if(net)
    {
        Etat* curr;
        Etat* tmp;
        netats.push_back(net);
        q.push(net);
        while(!q.empty())
        {
            curr = q.front();
            if(!curr)
            {
                cerr << "Erreur pop" << endl;
                exit(1);
            }
            q.pop();
            for(size_t i = 0; i < nb_symboles; i++)
            {
                //cout << "deter: " << curr->get_label() << ": "  << (char)('a' + i) << endl;
                net = get_old_transitions(curr, 'a' + i);
                if(net)
                {
                    cout << "net: " << net->get_label() << endl;
                    tmp = find_etat(netats, net);
                    if(tmp)
                    {
                        delete net;
                        net = tmp;
                    }
                    else
                    {
                        q.push(net);
                        netats.push_back(net);
                    }
                    Trs* trs_tmp = new Trs(curr,'a' + i, net);
                    ntrs.push_back(trs_tmp);
                    curr->add_succ(trs_tmp);
                    net->add_prec(trs_tmp);
                }
            }
        }
    }
    return Automate(nb_symboles,netats,ntrs);
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
