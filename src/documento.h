#ifndef GUARD_DOCUMENTO_H
#define GUARD_DOCUMENTO_H

#include "indice.h"
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

class Documento
{
    public:
        Documento();
        Documento(string id);
        string Get_id();
        void Inserir_coordenada(double coord);
        void Mudar_id(string id);
        double operator[](int indice);
        void Obter_coordenadas(Indice_invertido& Indice);
        void Imprimir_coordenadas();
        double Similaridade(Documento& x);

    private:
        string docid_;
        vector<double> coordenadas_;
	
	friend class Teste;
};

#endif // GUARD_DOCUMENTO_H
