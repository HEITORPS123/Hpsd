#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc,char* argv[]){
    int tamanho = 0;
    ifstream arq("q1.txt");
    string linha;
    vector<char> data;
    
    
    while(getline(arq,linha)){
        for(int i = 0;i < linha.size();i++){
            if((linha[i] != '-') && (linha[i] != ',') && (linha[i] != '!') && (linha[i] != '.') && (linha[i] != '?')){
                data.push_back(tolower(linha[i]));
            }
        }
        data.push_back(' ');
    }

    for(int i = 0;i < data.size();i++){
        cout << data[i];
    }
    cout << endl;
    system("pause");
    return 0;

}