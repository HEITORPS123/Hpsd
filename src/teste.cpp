#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "documento.h"
#include "indice.h"

#include <vector>
#include <map>
#include <string>

using std::vector;
using std::string;

const string path = "Documentos_Teste/";

class Teste
{
	public:
		static int NumDocumentos(Indice_invertido& i)
		{
			return i.numDocumentos_;
		}
		static vector<char> Data(Indice_invertido& i)
		{
			return i.data_;
		}
		static multimap<string, pair<string, int> > Indice(Indice_invertido& i)
		{
			return i.indice_;
		}
		static string Docid(Documento& d)
		{
			return d.docid_;
		}
		static vector<double> Coordenadas(Documento& d)
		{
			return d.coordenadas_;
		}
};

TEST_SUITE("Indice_invertido")
{
	TEST_CASE("Numdocs()")
	{
		Indice_invertido t(path);
		CHECK(t.Numdocs() == 3);
	}

	TEST_CASE("ler_arquivo()")
	{
		Indice_invertido t;
		t.ler_arquivo(path+"q3.txt");
		vector<char> vec, vec_classe = Teste::Data(t);
	
		string frase = "que nao tentamos ser uma casa como aquela";
		for (int i = 0; i < (int)frase.size(); i++)
			vec.push_back(static_cast<char>(frase[i]));
		vec.push_back(' ');

		REQUIRE(vec.size() == vec_classe.size());
		auto it = vec.begin();
		auto it2 = vec_classe.begin();
		for (; it != vec.end() && it2 != vec_classe.end(); it++, it2++)
			CHECK(*it == *it2);
	}

	TEST_CASE("Indice_invertido()")
	{
		Indice_invertido t(path);
		multimap<string, pair<string, int> > mp = Teste::Indice(t);
		
		CHECK(Teste::NumDocumentos(t) == 3);

		for (auto it = mp.begin(); it != mp.end(); it++)
			CHECK((it->second).second > 0);

		auto it2 = mp.begin();
		for (auto it = mp.begin(); it != mp.end(); it++)
		{
			it2 = it;
			it2++;

			while (it->first == it2->first)
			{
				CHECK((it->second).first != (it2->second).first);
				it2++;
			}
		}
	}
}

TEST_SUITE("Documento")
{
	TEST_CASE("Mudar_id(string id)")
	{
		Documento x("nome");
		CHECK(Teste::Docid(x) == "nome");

		x.Mudar_id("outro nome");
		CHECK(Teste::Docid(x) == "outro nome");
	}

	TEST_CASE("Inserir_coordenada(double coord)")
	{
		Documento x;

		for (int d = 0; d <= 10; d++)
			x.Inserir_coordenada(static_cast<double>(d));
	
		for (int k = 0; k <= 10; k++)
			CHECK(Teste::Coordenadas(x)[k] == static_cast<double>(k));
	}	

	TEST_CASE("Obter_coordenadas")
	{
		Indice_invertido t(path);
		Documento x(path + "q3.txt");
		x.Obter_coordenadas(t);

		int quantidade_palavras = 1;
		multimap<string, pair<string, int> > mp = Teste::Indice(t);
		auto it = mp.begin(); 
		string palavra_passada = it->first, palavra_atual;
		it++;
		for (; it != mp.end(); it++)
		{
			palavra_atual = it->first;

			if (palavra_atual != palavra_passada)
				quantidade_palavras++;

			palavra_passada = palavra_atual;
		}

		vector<double> vec = Teste::Coordenadas(x);
		CHECK(vec.size() == quantidade_palavras);

		double soma = 0.0;
		for (auto it = vec.begin(); it != vec.end(); it++)
		{
			soma += *it;
			CHECK(*it >= 0);
		}

		CHECK(soma > 0);
	}

	TEST_CASE("Similaridade(Documento& x)")
	{
		Indice_invertido t(path);
		Documento x(path+"q3.txt");		
		Documento query(path+"query.txt");
		
		x.Obter_coordenadas(t);
		query.Obter_coordenadas(t);

		CHECK(query.Similaridade(x) == x.Similaridade(query));
		CHECK(query.Similaridade(x) >= 0);
	}
}
