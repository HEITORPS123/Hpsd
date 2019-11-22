#include "indice.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstring>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

using std::string;  using std::ifstream;
using std::cout;    using std::remove;
using std::endl;    using std::ofstream;

vector<string> listar_arquivos()
{
	vector<string> vec;
	vec.push_back("Documentos/query.txt");
	std::string path = "Documentos/";
	for (const auto & entry : fs::directory_iterator(path))
	{
		string entry_path = entry.path();
		if (entry_path != "Documentos/query.txt")		
			vec.push_back(entry.path());
	}

	return vec;
}

Indice_invertido::Indice_invertido(){
    // pega o caminho (path) de todos os arquivos dentro da pasta Documentos e coloca no vetor documentos_nomes
  	vector<string> documentos_nomes = listar_arquivos();

	// loop que passa uma vez por cada documento dentro da pasta Documentos
	numDocumentos_ = 0;
	while (numDocumentos_ < (int)documentos_nomes.size())
	{
	   	// lê um documento	
	   	ler_arquivo(documentos_nomes[numDocumentos_]);

		// passa os dados do vetor para um ponteiro de char chamado vetor_data
  		char *temp, *vetor_data;
		vetor_data = new char[data_.size() + 1];
	   	for (int i = 0; i < (int)data_.size(); i++)
			vetor_data[i] = data_[i];

	   	vetor_data[data_.size()] = '\0';

		// remove os '\n' do vetor de caracteres
		*remove(vetor_data, vetor_data+strlen(vetor_data), '\n') = '\0';

		// loop que preenche o índice
	   	temp = strtok(vetor_data," ");
	   	while (temp)
	   	{
		   	string palavra = temp;
			// se a palavra não foi encontrada no índice
			if (indice_.find(palavra) == indice_.end())
				// adicione uma entrada no multimap do tipo palavra -> (nome do documento, frequencia = 1)
				indice_.insert(make_pair(palavra,make_pair(documentos_nomes[numDocumentos_],1)));

			// caso a palavra tenha sido encontrada, mas em outro documento
			else
			{
				bool found = false;
				auto range = indice_.equal_range(palavra);
				for (auto i = range.first; i != range.second; i++)
					if ((i->second).first == documentos_nomes[numDocumentos_])
					{
						++(i->second).second;   // incrementa a frequencia da palavra no arquivo atual
						found = true;
					}
				if (found == false)
					indice_.insert(make_pair(palavra,make_pair(documentos_nomes[numDocumentos_],1)));
			}
			temp = strtok(NULL," ");
	   	}
        data_.clear();
		numDocumentos_++;
	}
	
	cout << "Palavra\t\t |\t Frequencia" << endl;
	for (auto it = indice_.begin(); it != indice_.end(); it++)
		cout << it->first << "\t\t\t" << (it->second).first << ", " << (it->second).second << endl;

}

void Indice_invertido::ler_arquivo(string Nome_arquivo){
    ifstream arq(Nome_arquivo);
	string linha;

	// Loop que pega todas as linhas do documento e retira os caracteres especiais.
	while(getline(arq,linha))
	{
		for(int i = 0; i < (int)linha.size(); i++)
			if((linha[i] != '-') && (linha[i] != ',') && 
					(linha[i] != '!') && (linha[i] != '.') && (linha[i] != '?') && (linha[i] != '\n'))
				data_.push_back(tolower(linha[i]));
		data_.push_back(' ');
	}

	arq.close();
}

int Indice_invertido::Numdocs(){
    return numDocumentos_;
}

int Indice_invertido::count(string x){
    return indice_.count(x);
}

multimap<string,pair<string,int> >::iterator Indice_invertido::begin(){
    return indice_.begin();
}

multimap<string,pair<string,int> >::iterator Indice_invertido::end(){
    return indice_.end();
}
