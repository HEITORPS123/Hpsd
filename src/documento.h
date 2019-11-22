#ifndef GUARD_DOCUMENTO_H
#define GUARD_DOCUMENTO_H

#include "indice.h"
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

class Documento // Classe que representa um vetor no Rn associado a um documento.
{
    public:
        //Cria uma representação vetorial nula de um documento.
        Documento();
        //Cria uma representação vetorial nula de um documento com o nome id.
        Documento(string id);
        //Retorna o id do documento.
        string Get_id();
        //Insere uma coordenada no vector de coordenadas que representa o vetor Documento.
        void Inserir_coordenada(double coord);
        //Muda o id do documento.
        void Mudar_id(string id);
        //Acessa uma coordenada de um documento (leitura apenas).
        double operator[](int indice);
        //Constrói o vetor coordenadas_ do documento a partir do índice invertido.
        void Obter_coordenadas(Indice_invertido& Indice);
        //Imprime de maneira formatada as coordenadas do Documento.
        void Imprimir_coordenadas();
        //Calcula a similaridade de cosseno entre dois Documentos.
        double Similaridade(Documento& x);

    private:
        //Nome do documento associado ao vetor.
        string docid_;
        //Coordenadas do vetor.
        vector<double> coordenadas_;
	
	friend class Teste;
};

#endif // GUARD_DOCUMENTO_H
