//|###############################################################################|
//|==================== UNIVERSIDADE FEDERAL DE MINAS GERAIS =====================|
//|###############################################################################|
//| Nomes dos integrantes do Grupo: Heitor de Paula Santos Damasceno - 2019006671 |
//|                                 Antonio Isaac Lima                            |
//|									Arthur Resende Luz                            |
//| Turma: TN                                                                     |
//|-------------------------------------------------------------------------------|     
//|          TRABALHO PRÁTICO DE PROGRAÇÃO E DESENVOLVIMENTO DE SOFTWARE II       |
//|-------------------------------------------------------------------------------|

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>

#include "documento.h"

using std::cout;		using std::cin;		using std::map;
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
	cout << "Busca: ";
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

	map<long double, string> ranking;
	for(int i = 0;i < quantidade;i++){
		long double Sim = docs[i].Similaridade(docs[0]);
		cout << "sim(" << docs[i].Get_id() << ",Documentos/query.txt) = " << Sim << endl;
		ranking.insert(make_pair(Sim,docs[i].Get_id()));
	}

	cout << "CLASSIFICAÇÃO DOS ARQUIVOS:" << endl;
	for(auto it = ranking.begin();it != ranking.end();i++)
		cout << it->second << endl;

    cout << endl;

    return 0;
}
