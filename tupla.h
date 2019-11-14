#ifndef GUARD_TUPLA_H
#define GUARD_TUPLA_H

#include <string>
#include <vector>
#include <iostream>

class Tupla{
    public:
        Tupla(std::string id);
        int Frequencia();
        std::string Get_id();
        void operator++();
        Tupla operator*();
    
    private:
        std::string docid_;
        int freq_;
};

class Documento{
    public:
        Documento();
        Documento(std::string id);
        std::string Get_id();
        void Inserir_coordenada(double coord);
        void Mudar_id(std::string id);
        double operator[](int indice);
        void Imprimir_coordenadas(void);

    private:
        std::string docid_;
        std::vector<double> coordenadas_;
};

#endif
