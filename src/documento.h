#ifndef GUARD_DOCUMENTO_H
#define GUARD_DOCUMENTO_H

#include "indice.h"
#include <string>
#include <vector>
#include <iostream>

class Documento{
    public:
        Documento();
        Documento(std::string id);
        std::string Get_id();
        void Inserir_coordenada(double coord);
        void Mudar_id(std::string id);
        double operator[](int indice);
        void Obter_coordenadas(Indice_invertido& Indice);
        void Imprimir_coordenadas(void);
        double Similaridade(Documento& x);

    private:
        std::string docid_;
        std::vector<double> coordenadas_;
	friend class Teste;
};

#endif // GUARD_DOCUMENTO_H
