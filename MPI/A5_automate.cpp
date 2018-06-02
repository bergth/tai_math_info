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
    //cout << "nombre etat:" << nb_etats << endl;
    for(size_t i = 0; i < nb_etats; i++)
    {
        vector<int> nvec;
        nvec.push_back((int)(i));
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
        to = etats[u_stoi(tmp)];
        ajouter_transition(from,c,to);
    }
   this->sort();
}

Automate::Automate(size_t _nb_symboles, std::vector<Etat*> _etats, std::vector<Trs*> _trs)
{
    nb_symboles = _nb_symboles;
    nb_etats = _etats.size();
    etats = _etats;
    nb_transitions = _trs.size();
    transitions = _trs;
    nb_etatsInitiaux = 0;
    nb_etatsTerminaux = 0;
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
    this->sort();
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
    cout << "alphabet: ";
    for(size_t i = 0; i < nb_symboles; i++)
    {
        cout << (char)('a' + i);
    }
    cout << endl;
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

bool Automate::est_synchrone() const
{
    // On cherche simplement si une transition à comme charactère '*'.
    // À partir de là on est sur que l'automate n'est pas synchrone.
    for(size_t i = 0; i < nb_transitions; i++)
    {
        if(transitions[i]->tr == '*')
            return false;
    }
    return true;
}

bool Automate::est_deterministe() const
{
    if(nb_etatsInitiaux != 1)
    {
        return false;
    }
    // on teste la transition 0 à part pour le cas asynchrone
    // car notre boucle commence à 1
    if(nb_transitions == 0 && nb_symboles == 0)
        return true;

    if(transitions[0]->tr == '*')
    {
            return false;
    }
    for(size_t i = 1; i < nb_transitions; i++)
    {
        // Si l'automate est asynchrone, il n'est pas déterministe.
        if(transitions[i]->tr == '*')
        {
            return false;
        }
        // Les transitions sont triées. Il suffit donc juste de savoir si la transition
        // suivante est identique à la courante
        if(transitions[i]->from->get_vect_label() == transitions[i-1]->from->get_vect_label() &&
            transitions[i]->tr == transitions[i-1]->tr)
            {
                return false;
            }
    }
    return true;
}

Automate* Automate::determinisation_completion() const
{
    if(!est_synchrone())
    {
        return determiniser(true);
    }
    else
    {
        if(est_deterministe())
        {
            if(est_complet())
            {
                return copier();
            }
            else
            {
                return completer();
            }
        }
        else
        {
            return determiniser(false);
        }
    }
}


Automate* Automate::determiniser(bool asynchrone) const
{
    // Le vecteur contenant les nouveaux états
    vector<Etat*> netats;
    // on place un état puit (avec le nom '-1')
    vector<int> nvec;
    nvec.push_back(-1);
    Etat* puit = new Etat(nvec,false,false);
    netats.push_back(puit);
    // Cette file est utilisée pour la déterminisation
    // elle permet d'ajouter dans une sorte de file d'attente
    // les états à trouver.
    queue<Etat*> q;
    // Vecteur contenant les nouvelles transitions
    vector<Trs*> ntrs;
    for(size_t i = 0; i < nb_symboles; i++)
    {
        Trs* tmp = new Trs(puit,'a'+i,puit);
        ntrs.push_back(tmp);
        puit->add_prec(tmp);
        puit->add_succ(tmp);
    }
    // On créé le premier état initial composé des états initiaux de l'ancien automate
    Etat* net;
    if(asynchrone)
    {
        net = epsilon_cloture(etatsInitiaux);
    }
    else
    {
        net = contact_name_etat(etatsInitiaux);
    }
    net->set_ini(true);
    if(net)
    {
        Etat* curr;  // utilisé pour récupérer la tête de file
        Etat* tmp; // utilisé pour trouver un état
        netats.push_back(net);
        q.push(net); // on met le premier élément dans la file
        // tant que la file n'est pas vide, on continu
        while(!q.empty())
        {
            curr = q.front();
            if(!curr)
            {
                cerr << "Erreur pop" << endl;
                exit(1);
            }
            q.pop();
            // on test toutes les transitions pour l'état courant
            for(size_t i = 0; i < nb_symboles; i++)
            {
                if(asynchrone)
                {
                    net = epsilon_cloture(get_old_transitions(curr, 'a' + i));
                }
                else
                {
                    net = contact_name_etat(get_old_transitions(curr, 'a' + i)); // on récupère les transitions via le charactère 'a' + i partant de curr
                }
                if(net) // si on en trouve
                {
                    tmp = find_etat(netats, net); // on regarde si l'état a déjà été mis dans la liste des nouveaux états
                    if(tmp) // si oui, pas la peine de l'ajouter une deuxiéme fois
                    {
                        delete net;
                        net = tmp;
                    }
                    else // si non, on l'ajoute
                    {
                        q.push(net);
                        netats.push_back(net);
                    }
                }
                else // si on en trouve pas, on dirrige la nouvelle transitions vers le puit.
                {
                    net = puit;
                }
                // On créé une nouvelle transition et on l'ajoute là ou elle doit l'être.
                Trs* trs_tmp = new Trs(curr,'a' + i, net);
                ntrs.push_back(trs_tmp); // liste de transition générale
                curr->add_succ(trs_tmp); // liste des successeur de l'état courant
                net->add_prec(trs_tmp); // liste des prédécesseur de l'état vers lequel arrive la transition.
            }
        }
    }
    return new Automate(nb_symboles,netats,ntrs);
}


bool Automate::est_complet() const
{
    if(nb_etatsInitiaux != 1)
        return false;
    if(nb_transitions == 0 && nb_symboles == 0)
        return true;
    // si il y a zero transitions, il ne peut être complet.
    if(nb_transitions == 0)
        return false;
    // on utilise c pour tester si les transitions se suivent bien.
    // on peut faire celà car les transitions sont triées.
    for(size_t i = 0; i < nb_etats; i++)
    {
        vector<Trs*> tmp = etats[i]->get_succ();
        if(tmp.size() != nb_symboles)
            return false;
        for(size_t j = 0; j < tmp.size(); j++)
        {
            if(tmp[j]->tr != (char)('a' + j))
                return false;
        }
    }
    return true;
}

bool Automate::est_Standard() const
{
    if(nb_etatsInitiaux != 1)
        return false;
    for(size_t i = 0; i < nb_transitions; i++)
    {
        if(transitions[i]->to == etatsInitiaux[0])
            return false;
    }
    return true;

}

Automate* Automate::standardiser()
{

}

Automate* Automate::copier() const
{
    // vecteur des nouveaux états
    vector<Etat*> netats;
    // vecteur des nouvelles transitions
    vector<Trs*> ntrs;
    // vecteur temporaire pour stocker les transitions partante d'un état
    vector<Trs*> tmp;
    // création et ajout d'un vecteur puit dans netats
    vector<int> nvec;

    // pour tous les états de l'automate actuel
    for(size_t i = 0; i < etats.size(); i++)
    {
        // on regarde si l'état existe ou non
        Etat* from = find_etat(netats,etats[i]);
        if(!from) // si non, on créer un nouvel état "copie" et on l'ajoute dans le vecteur
        {
            from = new Etat(etats[i]->get_vect_label(),etats[i]->get_ini(),etats[i]->get_ter());
            netats.push_back(from);
        }
        tmp = etats[i]->get_succ(); // on récupère les transitions vers les successeurs
        char ctmp = 0;
         // on passe sur toutes les transitions
        for(size_t j = 0; j < tmp.size(); j++)
        {
            Etat* to;
            // si on est pas déjà passé sur toutes les transitions et que c est différent de la transitions courante
            // c'est à dire, si nous sommes sur une transition qui n'existe pas
            ctmp = tmp[j]->tr; // la transition vaux celle de la transition courante
            to = find_etat(netats,tmp[j]->to); // on cherche l'état de la destination de la transition
            if(!to) // si il n'existe pas dans le vecteur, on le créé et on l'ajoute
            {
                to = new Etat(tmp[j]->to->get_vect_label(),tmp[j]->to->get_ini(),tmp[j]->to->get_ter());
                netats.push_back(to);
            }
            // on créé la transition et on l'ajoute là ou il faut
            Trs* newtrs = new Trs(from,ctmp,to);
            ntrs.push_back(newtrs);
            from->add_succ(newtrs);
            to->add_prec(newtrs);

        }
    }
    // on créé un nouvel automate à partir du vecteur de nouveaux états et de nouvelles transitions
    return new Automate(nb_symboles,netats,ntrs);
}

Automate* Automate::completer() const
{
    // vecteur des nouveaux états
    vector<Etat*> netats;
    // vecteur des nouvelles transitions
    vector<Trs*> ntrs;
    // vecteur temporaire pour stocker les transitions partante d'un état
    vector<Trs*> tmp;
    // création et ajout d'un vecteur puit dans netats
    vector<int> nvec;
    nvec.push_back(-1);
    Etat* puit = new Etat(nvec,false,false);
    netats.push_back(puit);
    // on ajoute toutes les transitions allant du puit vers le puit
    for(size_t i = 0; i < nb_symboles; i++)
    {
        Trs* tmp = new Trs(puit,'a'+i,puit);
        ntrs.push_back(tmp);
        puit->add_prec(tmp);
        puit->add_succ(tmp);
    }
    // pour tous les états de l'automate actuel
    for(size_t i = 0; i < etats.size(); i++)
    {
        char c = 'a';
        // on regarde si l'état existe ou non
        Etat* from = find_etat(netats,etats[i]);
        if(!from) // si non, on créer un nouvel état "copie" et on l'ajoute dans le vecteur
        {
            from = new Etat(etats[i]->get_vect_label(),etats[i]->get_ini(),etats[i]->get_ter());
            netats.push_back(from);
        }
        tmp = etats[i]->get_succ(); // on récupère les transitions vers les successeurs
        size_t j = 0;
        char ctmp = 0;
        while(c < (char)('a' + nb_symboles)) // on passe sur toutes les transitions
        {
            Etat* to;
            // si on est pas déjà passé sur toutes les transitions et que c est différent de la transitions courante
            // c'est à dire, si nous sommes sur une transition qui n'existe pas
            if(j >= tmp.size() || c != tmp[j]->tr)
            {
                ctmp = c; // la transition vaut c
                to = puit; // la destination de la transition est le puit.
            }
            else
            {
                ctmp = tmp[j]->tr; // la transition vaux celle de la transition courante
                to = find_etat(netats,tmp[j]->to); // on cherche l'état de la destination de la transition
                if(!to) // si il n'existe pas dans le vecteur, on le créé et on l'ajoute
                {
                    to = new Etat(tmp[j]->to->get_vect_label(),tmp[j]->to->get_ini(),tmp[j]->to->get_ter());
                    netats.push_back(to);
                }
                j++; // on a passé une transition, on incrémente j.
            }
            c++; // on incrémente c pour tester la prochaine transition
            // on créé la transition et on l'ajoute là ou il faut
            Trs* newtrs = new Trs(from,ctmp,to);
            ntrs.push_back(newtrs);
            from->add_succ(newtrs);
            to->add_prec(newtrs);
        }
    }
    // on créé un nouvel automate à partir du vecteur de nouveaux états et de nouvelles transitions
    return new Automate(nb_symboles,netats,ntrs);
}

bool Automate::reconnaitre_mot(string mot)
{
    // Si l'automate n'est pas déterministe, on ne peut pas tester le mot facilement sans transformation.
    if(!est_deterministe())
    {
        Automate* B = determinisation_completion();
        bool res = B->reconnaitre_mot(mot);
        delete B;
        return res;
    }
    // On se place sur le seul état initial (car déterministe)
    Etat* curr = etatsInitiaux[0];
    // on parcours tout le mot
    for(size_t i = 0; i < mot.size(); i++)
    {
        // on récupère les transitions de l'état courant
        vector<Trs *> tr_tmp = curr->get_succ();
        curr = NULL;
        for(size_t j = 0; j < tr_tmp.size(); j++)
        {
            // si une transition correspond à la lettre de notre mot
            if(tr_tmp[j]->tr == mot[i])
            {
                // on se place sur la destination de cette transition
                curr = tr_tmp[j]->to;
            }
        }
        // si on a pas trouvé de transition correspondant à la lettre courante, le mot n'est pas reconnu
        if(curr == NULL)
        {
            return false;
        }
    }
    // nous avons parcouru tout notre mot, on regarde si l'état sur lequel on est est terminal.
    if(curr->get_ter())
    {
        return true;
    }
    return false;
}

void Automate::trouver_n_premiers_mots(size_t n, size_t l)
{
    vector<string> res;
    if(reconnaitre_mot(""))
    {
        res.push_back("");
    }
    queue<string> q;
    q.push("");
    while(!q.empty())
    {
        string tmp = q.front();
        if(res.size() == n || tmp.size() == l)
        {
            break;
        }
        q.pop();
        for(size_t i = 0; i < nb_symboles; i++)
        {
            string tmp2 = tmp + (char)('a' + i);
            //cout << "d: " << tmp2 << endl;
            q.push(tmp2);
            if(reconnaitre_mot(tmp2))
                res.push_back(tmp2);
        }
    }
    for(size_t i = 0; i < res.size(); i++)
    {
        if(res[i] == "")
            cout << "<e>,";
        else
            cout << res[i] + ", ";
    }
    cout << endl;
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
