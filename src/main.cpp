#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>

#include "documento.h"

using std::cout;		using std::cin;
using std::endl;		using std::ofstream;
using std::string;		using std::vector;

const string path = "Documentos/";

void ler_query()
{
    ofstream query;
    string linha;

    query.open("Documentos/query.txt");
    getline(cin,linha);
    query << linha;
    query.close();   
}

// apesar de estar definida em indice.h, precisamos declará-la aqui também!
vector<string> listar_arquivos(string path);

int main()
{
	ler_query();
	Indice_invertido Indice(path);
	Documento* docs;
	vector<string> arquivos = listar_arquivos(path);
	int quantidade = arquivos.size();

	docs = new Documento[quantidade];
	
	int i = 0;
	for (auto it = arquivos.begin(); it != arquivos.end(); it++, i++)
		docs[i].Mudar_id(*it);

	for(int i = 0; i < quantidade; i++)
		docs[i].Obter_coordenadas(Indice);

	for(int i = 0;i < quantidade;i++)
		cout << "sim(" << docs[i].Get_id() << ",Documentos/query.txt) = " << docs[i].Similaridade(docs[0]) << endl;

    cout << endl;
    return 0;
}
