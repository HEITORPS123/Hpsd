#include "documento.h"
#include <cmath>

using std::string;
using std::vector;
using std::cout;

Documento::Documento(){
}

Documento::Documento(std::string id){
    docid_ = id;
}

void Documento::Mudar_id(std::string id){
    docid_ = id;
}

std::string Documento::Get_id(){
    return docid_;
}

void Documento::Inserir_coordenada(double coord){
    coordenadas_.push_back(coord);
}

double Documento::operator[](int indice){
    return coordenadas_[indice];
}

void Documento::Imprimir_coordenadas(){
    cout << docid_ << " = {";
    for (int i = 0; i < coordenadas_.size() - 1; i++)
        cout << coordenadas_[i] << ", ";

    cout << coordenadas_[coordenadas_.size()-1] << "}\n";
}

double Documento::Similaridade(Documento& query){
    double somatorio_produto,somatorio_quadrado1,somatorio_quadrado2,cos;
    
    somatorio_produto = 0;
    for(int i = 0;i < coordenadas_.size();i++)
        somatorio_produto += coordenadas_[i]*(query.coordenadas_[i]);
    
    somatorio_quadrado1 = 0;
    for(int i = 0;i < coordenadas_.size();i++)
        somatorio_quadrado1 += (coordenadas_[i]*coordenadas_[i]);
    
    for(int i = 0;i < query.coordenadas_.size();i++)
        somatorio_quadrado2 += (query.coordenadas_[i])*(query.coordenadas_[i]);
    
    cos = (somatorio_produto)/(sqrt(somatorio_quadrado1)*sqrt(somatorio_quadrado2));
    return cos;
}
