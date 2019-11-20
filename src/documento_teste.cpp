#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "documento.h"

#include "doctest.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>


class Teste {
	public:
	static string Docid(Documento& c){return c.docid_;};
	static vector<double> Coordenadas(Documento& c){return c.coordenadas_;};
};

TEST_SUITE("documento") {
	TEST_CASE("Documento()") {
		Documento doc;
		CHECK(Teste::Docid(doc) == "");
		CHECK(Teste::Coordenadas(doc).size() == 0);
	}

	TEST_CASE("Documento(string)") {
		Documento doc("documento1");
		CHECK(Teste::Docid(doc) == "documento1");
		CHECK(Teste::Coordenadas(doc).size() == 0);
	}

	TEST_CASE("Get_id()") {
		Documento doc("documento1"),doc2("documento2");
		CHECK(doc.Get_id() == "documento1");
		CHECK(doc.Get_id() == "documento2");
	}

	TEST_CASE("Inserir_coordenada(double)") {
		Documento doc;
		doc.Inserir_coordenada
	}

	TEST_CASE("Mudar_id(string)") {
		
	}

	TEST_CASE("Imprimir_coordenadas(void)") {
	
	}
} // end TEST_SUITE("documento") 
