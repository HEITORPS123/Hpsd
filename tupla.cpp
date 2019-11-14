#include "tupla.h"

using std::string;
using std::vector;
using std::cout;

Tupla::Tupla(string id)
{
    docid_ = id;
    freq_ = 1;
}

int Tupla::Frequencia()
{ 
    return freq_;
}

string Tupla::Get_id()
{
    return docid_; 
}

Tupla Tupla::operator*(){
    return *this;
}

void Tupla::operator++(){
    freq_++;
}

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
