#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>

#include "tupla.h"
#include "documento.h"

using std::cout;		using std::cin;        	using std::multimap; using std::ofstream;
using std::endl;		using std::vector;		using std::remove;
using std::string;		using std::ifstream;	using std::pair;

void ler_query(){
    ofstream query;
    string linha;

    query.open("Documentos/query.txt");
    getline(cin,linha);
    query << linha;
    query.close();   
}

void ler_arquivos(string Nome_arquivo, vector<char>& data)
{
	ifstream arq(Nome_arquivo);
	string linha;

	// Loop que pega todas as linhas do documento e retira os caracteres especiais.
	while(getline(arq,linha))
	{
		for(int i = 0; i < (int)linha.size(); i++)
			if((linha[i] != '-') && (linha[i] != ',') && 
					(linha[i] != '!') && (linha[i] != '.') && (linha[i] != '?') && (linha[i] != '\n'))
				data.push_back(tolower(linha[i]));
		data.push_back(' ');
	}

	arq.close();
}

int criar_indice(multimap<string,pair<string,int> >& Indice)
{
   	// pega o caminho (path) de todos os arquivos dentro da pasta Documentos e coloca no vetor documentos_nomes
  	vector<string> documentos_nomes;
	documentos_nomes.push_back("Documentos/query.txt");
	documentos_nomes.push_back("Documentos/q1.txt");
	documentos_nomes.push_back("Documentos/q2.txt");
	documentos_nomes.push_back("Documentos/q3.txt");
	
	// loop que passa uma vez por cada documento dentro da pasta Documentos
	int num_documento = 0;
	while (num_documento < (int)documentos_nomes.size())
	{
	   	// lê um documento	
		vector<char> data;
	   	ler_arquivos(documentos_nomes[num_documento], data);

		// passa os dados do vetor para um ponteiro de char chamado vetor_data
  		char *temp, *vetor_data;
		vetor_data = new char[data.size() + 1];
	   	for (int i = 0; i < (int)data.size(); i++)
			vetor_data[i] = data[i];

	   	vetor_data[data.size()] = '\0';

		// remove os '\n' do vetor de caracteres
		*remove(vetor_data, vetor_data+strlen(vetor_data), '\n') = '\0';

		// loop que preenche o índice
	   	temp = strtok(vetor_data," ");
	   	while (temp)
	   	{
		   	string palavra = temp;
			// se a palavra não foi encontrada no índice
			if (Indice.find(palavra) == Indice.end())
				// adicione uma entrada no multimap do tipo palavra -> (nome do documento, frequencia = 1)
				Indice.insert(make_pair(palavra,make_pair(documentos_nomes[num_documento],1)));

			// caso a palavra tenha sido encontrada, mas em outro documento
			else
			{
				bool found = false;
				auto range = Indice.equal_range(palavra);
				for (auto i = range.first; i != range.second; i++)
					if ((i->second).first == documentos_nomes[num_documento])
					{
						++(i->second).second;   // incrementa a frequencia da palavra no arquivo atual
						found = true;
					}
				if (found == false)
					Indice.insert(make_pair(palavra,make_pair(documentos_nomes[num_documento],1)));
			}
			temp = strtok(NULL," ");
	   	}
		num_documento++;
	}
	
	cout << "Palavra\t\t |\t Frequencia" << endl;
	for (auto it = Indice.begin(); it != Indice.end(); it++)
		cout << it->first << "\t\t\t" << (it->second).first << ", " << (it->second).second << endl;
	
	return num_documento;
}

void obter_coordenadas(multimap<string,pair<string,int> >& Indice, char* query, int num_documento)
{
	char* temp;
	int tf;
	double idf,W;
	Documento* docs;
	string palavra_anterior;
	bool adicionado;

	docs = new Documento[num_documento];
	docs[0].Mudar_id("Documentos/query.txt");
	docs[1].Mudar_id("Documentos/q1.txt");
	docs[2].Mudar_id("Documentos/q2.txt");
	docs[3].Mudar_id("Documentos/q3.txt");

	for (int j = 0; j < num_documento; j++) //Itera por todos os documentos para construir as coordenadas de cada estrutura de dados "Documento"
	{
		// Aqui temos que pegar a frequência de cada palavra em cada documento para calcular as coordenadas,
		// mas como alguns documentos não tem certas palavras, tem algumas modificações. O for itera sobre todas
		// as entradas do índice, calculando a coordenada se a palavra está presente no documento.Se a palavra
		// muda , e não é adicionada para determinado documento, significa que não está naquele documento, então
		// a coordenada é 0.0. Se a palavra não muda, vai iterando para saber se a palavra está no documento. 
		palavra_anterior = "apartamento";
		adicionado = false;
		for (auto i = Indice.begin(); i != Indice.end(); i++) 
		{
			if (((i->first) != palavra_anterior) && (adicionado == false)) //Não está presente no documento j a palavra
			{
				docs[j].Inserir_coordenada(0.0);
				palavra_anterior = (i->first);
			}
			if ((i->second).first == docs[j].Get_id()) //Está presente no documento j
			{
				//Os cálculos a seguir são literalmente tirados das orientações do trabalho, com os mesmos nomes de variável
				idf = log10(((double)num_documento + 1)/(double)Indice.count(i->first));
				W = ((i->second).second)*idf;
				docs[j].Inserir_coordenada(W);
				adicionado = true;
			}else if (adicionado == true && palavra_anterior != i->first) //Se a palavra mudou mas foi adicionada,retorna ao estado original
			{
				adicionado = false;
				palavra_anterior = (i->first);
			}					
		}
	}

	for (int i = 0; i < num_documento; i++)
		docs[i].Imprimir_coordenadas();

	for(int i = 1;i < num_documento;i++){
		cout << "sim("<<docs[i].Get_id() << ",query) = "<< docs[i].Similaridade(docs[0]) << endl;
	}

	delete [] docs;
}

int main(){
	int num_documentos;
	multimap<string,pair<string,int> > Indice;
	vector<char> Busca;
	char* blah;
	ler_query();
    num_documentos = criar_indice(Indice);

	obter_coordenadas(Indice,blah,num_documentos);

    cout << endl;
    return 0;
}
