#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include "tupla.h"

using std::cout;		using std::cin;        using std::multimap;
using std::endl;		using std::vector;
using std::string;		using std::ifstream;	

vector<char> data;

void ler_arquivos(string Nome_arquivo)
{
    int tamanho = 0;
    ifstream arq(Nome_arquivo);
    string linha;
    
    // Loop que pega todas as linhas do documento e retira os caracteres especiais.
    while(getline(arq,linha))
	{
        for(int i = 0; i < linha.size(); i++)
            if((linha[i] != '-') && (linha[i] != ',') && 
							(linha[i] != '!') && (linha[i] != '.') && (linha[i] != '?'))
                data.push_back(tolower(linha[i]));
        data.push_back(' ');
	}

    for(int i = 0; i < data.size(); i++)
        cout << data[i];

    cout << endl;
}

void Criar_indice(){
    multimap<string,Tupla*> Indice;
    char *temp,*vetor_data;
    string palavra,documento_nome;
    int num_documentos;

    vetor_data = new char[data.size() + 1];
    for(int i = 0;i < data.size();i++){
        vetor_data[i] = data[i];
    }
    
    vetor_data[data.size()] = '\0';

    temp = strtok(vetor_data," ");
    while (temp)
    {
        palavra = temp;
        if(Indice.find(palavra) == Indice.end()){
            Indice.insert(make_pair(palavra,new Tupla(documento_nome))); //Separa as palavras pelo " " entre cada uma;
        }else{
            (*((Indice.find(palavra))->second))++;      // Meio confuso, mas basicamente , se a palavra já foi inserida no índice, chama função Tupla++ (incrementa frequência).
        }
        temp = strtok(NULL," ");
    }

    cout << "Palavra    |   Frequencia" << endl;
    for(auto i = Indice.begin();i != Indice.end();i++){
        cout << i->first << "    " << (i->second)->Frequencia() << endl;    
    }
    cout << endl;
}

int main(int argc,char* argv[]){
    string Arq = "q1.txt";
    ler_arquivos(Arq);
    Criar_indice();
    cout << endl;
    return 0;
}