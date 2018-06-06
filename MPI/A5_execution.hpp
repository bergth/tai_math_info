#include<string>
#include "A5_automate.h"

Automate* lire_automate(size_t n);
std::string lire_mot();
void reconnaissance_de_mots(const Automate* A);
void language_complementaire(const Automate* A);
void standardisation(const Automate* A);
void traitements(const Automate* A);
void test_standard(const Automate* A);