#include "A5_automate.h"
#include <vector>

class Interface
{
    private:
        std::vector<Automate*> auts;
        std::vector<std::string> orgs;
        size_t nb;
        std::string str;
        void traitement();
        void clear();
        void lister_automates();
        void help();
    public:
        Interface();
        ~Interface();
        void start();

};


