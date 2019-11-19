#include "documento.h"

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
    for (int i = 0; i < coordenadas_.size(); i++)
        cout << coordenadas_[i] << ", ";

    cout << "}\n";
}

