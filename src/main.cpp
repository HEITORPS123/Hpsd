#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#include "documento.h"

using std::cout;		using std::cin;
using std::endl;		using std::ofstream;
using std::string;			

void ler_query(){
    ofstream query;
    string linha;

    query.open("Documentos/query.txt");
    getline(cin,linha);
    query << linha;
    query.close();   
}

int main(){
	ler_query();
	Indice_invertido Indice;
	Documento* docs;

	docs = new Documento[4];
	docs[0].Mudar_id("Documentos/query.txt");
	docs[1].Mudar_id("Documentos/q1.txt");
	docs[2].Mudar_id("Documentos/q2.txt");
	docs[3].Mudar_id("Documentos/q3.txt");
	

	for(int i = 0;i < 4;i++)
		docs[i].Obter_coordenadas(Indice);

	for(int i = 0;i < 4;i++)
		cout << "sim(" << docs[i].Get_id() << ",query) = " << docs[i].Similaridade(docs[0]) << endl;

    cout << endl;
    return 0;
}
