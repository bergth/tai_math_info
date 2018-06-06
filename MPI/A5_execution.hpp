#include<string>
#include "A5_automate.h"

// lit un automate avec n entre 1 et 42
Automate* lire_automate(size_t n);
// lit un mot et le retourne dans un string
std::string lire_mot();
// reconnait un mot pour un automate A comme indiqu� dans le sujet du projet
void reconnaissance_de_mots(const Automate* A);
// applique la complementarisation comme indiqu� dans le sujet du projet
void language_complementaire(const Automate* A);
// implique tous les traitements, de automate fini � minimisation + compl�tion et standardisation
void traitements(const Automate* A);
// fait le test de standardisation comme indiqu� dans le sujet.
void test_standard(const Automate* A);
