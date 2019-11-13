#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "tupla.h"
// ambos utilizados para vasculhar a pasta Documentos

using std::cout;		using std::cin;        	using std::multimap;
using std::endl;		using std::vector;		using std::remove;
using std::string;		using std::ifstream;	

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

void criar_indice(multimap<string,Tupla*> Indice)
{
   	// pega o caminho (path) de todos os arquivos dentro da pasta Documentos e coloca no vetor documentos_nomes
  	vector<string> documentos_nomes;
	documentos_nomes.push_back("q1.txt");
	documentos_nomes.push_back("q2.txt");
	documentos_nomes.push_back("q3.txt");
	
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
				Indice.insert(make_pair(palavra,new Tupla(documentos_nomes[num_documento])));        
			// caso a palavra tenha sido encontrada, mas em outro documento
			else{ //A mudança vai daqui -----------------------------
				bool achou = false;
				auto range = Indice.equal_range(palavra);
				for(auto i = range.first;i != range.second;i++){
					if(((i->second)->Get_id()) == documentos_nomes[num_documento]){
						++(*(i->second));   // incrementa a frequencia da palavra no arquivo atual
						achou = true;
					}
				}
				if(achou == false){
					Indice.insert(make_pair(palavra,new Tupla(documentos_nomes[num_documento])));
				}
			} // Até aqui----------------------------------------------
			temp = strtok(NULL," ");
	   	}
		num_documento++;
	}
	
	cout << "Palavra\t\t |\t Frequencia" << endl;
	for(auto it = Indice.begin(); it != Indice.end(); it++)
		cout << it->first << "\t\t\t" << (it->second)->Get_id() << ", " << (it->second)->Frequencia() << endl;
}

//Mudança começa aqui================================================
void obter_coordenadas(multimap<string,Tupla*> Indice,char* query){
	char* temp;
	int tf;
	double idf,W;
	
	temp = strtok(query," ");
	while(temp)
	{
		string palavra = temp;
		idf = log10(((int)num_documento + 1)/Indice.count(palavra));
		W = ((Indice.find(palavra)).Frequencia())*idf;
	}
}
//Termina aqui=======================================================

int main(){
	multimap<string,Tupla*> Indice;
    criar_indice(Indice);
    cout << endl;
    return 0;
}
