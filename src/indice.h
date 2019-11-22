#ifndef GUARD_INDICE_H
#define GUARD_INDICE_H

#include <string>
#include <map>
#include <vector>

using std::multimap;  using std::vector;
using std::string;
using std::pair;

class Indice_invertido 
{ 
    public:
		//Construtor vazio do Indice_invertido.
		Indice_invertido();
		//Constói o Indice_invertido a partir de uma lista com o nome dos documentos a serem lidos e processados.
		Indice_invertido(string path);
		//Método que lê cada arquivo separadamente e armazena o resultado no vector data_ (usado no construtor).
		void ler_arquivo(string Nome_arquivo);
		//Retorna o número de documentos presentes do índice.
		int Numdocs();
		//Retorna um iterador para o início do índice.
		multimap<string, pair<string, int> >::iterator begin();
		//Retorna um iterador que simboliza o final do índice.
		multimap<string, pair<string, int> >::iterator end();
		//Retorna o número de vezes que uma chave (palavra) aparece no índice.
		int count(string x);

    private:
		//Índice em si (mapeia as palavras para um par com <Nome do Documento,frequência no Documento>).
		multimap<string, pair<string, int> > indice_;
		//Vector onde os dados lidos em cada documento são armazenados. 
		vector<char> data_;
		//Número de documentos lidos e inseridos no índice.
		int numDocumentos_;

    friend class Teste;
};
#endif // GUARD_INDICE_H
