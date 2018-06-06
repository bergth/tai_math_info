#include<string>
#include<vector>

// sépare une string en différentes string avec l'espage
std::vector<std::string> string_to_strvec(std::string str);
// prend une string contenant que des entiers séparés par un espace et retourne un vecteur de int
std::vector<int> u_string_to_intvec(std::string str);
// convertis un entier en string
std::string u_to_string(int val);
// convertis un entier dans un string  de taille n
std::string u_to_nstring(int val, size_t n);
// convertis une string en entier
int u_stoi(const std::string& str);
