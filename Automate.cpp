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
        etats[val]->set_ini(true);
        etatsInitiaux.push_back(etats[val]);
    }
    
    // lecture etats finaux
    getline(file,line);
    read = string_to_intvec(line);
    nb_etatsTerminaux = read[0];
    for(size_t i = 1; i < nb_etatsTerminaux + 1; i++)
    {
        val = read[i];
        etats[val]->set_ter(true);
        etatsTerminaux.push_back(etats[val]);
    }

    // lecture nombre de transitions
    getline(file,line);
    nb_transitions = stoi(line);
    for(size_t j = 0; j < nb_transitions; j++)
    {
        // lecture transitions
        Etat* from = nullptr;
        Etat* to = nullptr;
        char c = 0;
        string tmp = "";
        getline(file,line);
        size_t i = 0;
        while(i < line.size() && line[i] >= '0' && line[i] <= '9')
        {
            tmp += line[i];
            i++;
        }
        from = etats[stoi(tmp)];
        c = line[i];
        if(i < line.size())
            i++;
        tmp = "";
        while(i < line.size() && line[i] >= '0' && line[i] <= '9')
        {
            tmp += line[i];
            i++;
        }
        to = etats[stoi(tmp)];
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

tr_t* Automate::ajouter_transition(Etat* from, char c, Etat* to)
{
    tr_t* tmp_tr = new tr_t;
    get<0>(*tmp_tr) = from;
    get<1>(*tmp_tr) = c;
    get<2>(*tmp_tr) = to;
    from->add_prec(tmp_tr);
    to->add_succ(tmp_tr);
    transitions.push_back(tmp_tr);
    return tmp_tr;
}

string Automate::to_dot()
{
    vector<tr_t*>::iterator it;
    string str = "digraph G {\n";
    string init = "";
    string trans = "";
    for(it = transitions.begin(); it != transitions.end(); it++)
    {
        string name_from = get<0>(**it)->get_label();
        char c = get<1>(**it);
        string name_to = get<2>(**it)->get_label();
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
        init  +=    "    node [shape = point, color = white, fontcolor = white]; start" + to_string(i) + ";\n";
        trans +=    "    start" + to_string(i) + " -> \"" + (*eit)->get_label() + "\";\n";
        i++;
    }

    i = 0;
    for(eit = etatsTerminaux.begin(); eit != etatsTerminaux.end(); eit++)
    {
        init  +=    "    node [shape = point, color = white, fontcolor = white]; end" + to_string(i) + ";\n";
        trans +=    "   \"" + (*eit)->get_label() + "\" ->  end" + to_string(i) + " ;\n";
        i++;
    }

    init += "    node [shape = circle, color = black, fontcolor = black];\n";
    str += init;
    str += trans;
    str += "}\n";
    return str;
}