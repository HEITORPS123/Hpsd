#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Tupla{
    public:
    Tupla(string id):docid_(id),freq_(1){};
    int Frequencia(void){ return freq_;};
    string Get_id(void){return docid_; };
    void operator++(int);
    Tupla operator*();
    private:
    string docid_;
    int freq_;
};

int main(int argc,char* argv[]){
    int tamanho = 0;
    ifstream arq("q1.txt");
    string linha;
    vector<char> data;
    multimap<string,Tupla*> Indice;
    char *temp,*vetor_data;
    string palavra,documento_nome;
    int num_documentos;

     while(getline(arq,linha)){
        for(int i = 0;i < linha.size();i++){
            if((linha[i] != '-') && (linha[i] != ',') && (linha[i] != '!') && (linha[i] != '.') && (linha[i] != '?')){
                data.push_back(tolower(linha[i]));
            }
        }
        data.push_back(' ');
    }

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
            Indice.insert(make_pair(palavra,new Tupla(documento_nome)));
        }else{
            (*((Indice.find(palavra))->second))++;
        }
        temp = strtok(NULL," ");
    }

    cout << "Palavra    |   Frequencia" << endl;
    for(auto i = Indice.begin();i != Indice.end();i++){
        cout << i->first << "    " << (i->second)->Frequencia() << endl;
    }
    cout << endl;
    system("pause");
    return 0;
}


Tupla Tupla::operator*(void){
    return *this;
}

void Tupla::operator++(int){
    freq_++;
}
