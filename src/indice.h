#ifndef GUARD_INDICE_H
#define GUARD_INDICE_H

#include <string>
#include <map>

class Indice_invertido{
    public:
    Indice_invertido();
    private:
    multimap<string,pair<string,int> > indice_;
    int numDocumentos_;
};

#endif // GUARD_INDICE_H