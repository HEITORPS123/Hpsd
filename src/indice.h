#ifndef GUARD_INDICE_H
#define GUARD_INDICE_H

#include <string>
#include <map>
#include <vector>

using std::multimap;  using std::vector;
using std::string;
using std::pair;

class Indice_invertido{ 
    public:
    Indice_invertido();
    void ler_arquivo(string Nome_arquivo);
    int Numdocs();
    multimap<string,pair<string,int> >::iterator begin();
    multimap<string,pair<string,int> >::iterator end();
    int count(string x);

    private:
    multimap<string,pair<string,int> > indice_;
    vector<char> data_;
    int numDocumentos_;

    friend class Teste;
};
#endif // GUARD_INDICE_H