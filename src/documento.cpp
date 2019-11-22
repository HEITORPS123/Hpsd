#include "documento.h"
#include "indice.h"
#include <cmath>
#include <map>

using std::string; using std::multimap;
using std::vector; using std::pair;
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

void Documento::Obter_coordenadas(Indice_invertido& Indice)
{
	char* temp;
	int tf;
	double idf,W;
	string palavra_anterior;
	bool adicionado;

	// Aqui temos que pegar a frequência de cada palavra em cada documento para calcular as coordenadas,
	// mas como alguns documentos não tem certas palavras, tem algumas modificações. O for itera sobre todas
	// as entradas do índice, calculando a coordenada se a palavra está presente no documento.Se a palavra
	// muda , e não é adicionada para determinado documento, significa que não está naquele documento, então
	// a coordenada é 0.0. Se a palavra não muda, vai iterando para saber se a palavra está no documento.
	bool possui = false;	
	for (auto it = Indice.begin(); it != Indice.end();)
	{
		auto it2 = it;
		while (it->first == it2->first)
		{
			if ((it2->second).first == Get_id())
				possui = true;			
			it2++;
		}

		if (!possui)
			Inserir_coordenada(0.0);
		else
		{
			idf = log10(((double)Indice.Numdocs() + 1)/(double)Indice.count(it->first));
			W = ((it->second).second)*idf;
			Inserir_coordenada(W);
			possui = false;
		}
		it = it2;
	}

	Imprimir_coordenadas();
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
