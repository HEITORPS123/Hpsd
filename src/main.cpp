//|###############################################################################|
//|==================== UNIVERSIDADE FEDERAL DE MINAS GERAIS =====================|
//|###############################################################################|
//| Nomes dos integrantes do Grupo: Heitor de Paula Santos Damasceno - 2019006671 |
//|                                 Antônio Isaac Silva Lima - 2019006361         |
//|									Arthur Luz  -  2019006396                     |
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
	cout << "Busca\n> ";
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

	map<double, string> ranking;
	for(int i = 0;i < quantidade;i++){
		double sim = docs[0].Similaridade(docs[i]);
		ranking.insert(make_pair(sim,docs[i].Get_id()));
	}

	int mostrar_pag;
	cout << "Quantos arquivos, no máximo, serão mostrados por vez\n> ";
  	cin >> mostrar_pag;
	cin.ignore();	

	int ij = 0;
	cout << "\nCLASSIFICAÇÃO DOS ARQUIVOS:" << endl;
	for(auto it = ranking.rbegin(); it != ranking.rend(); it++)
	{
		if (it->first != 0.0 && it->second != path+"query.txt")
			cout << it->second << "\t(" << it->first << ")\n";
		if (ij == mostrar_pag)
		{
			cin.ignore();
			ij=0;
		}
		ij++;
	}
   cout << endl;

   return 0;
}
