/*
* Universidade de Brasília
* Departamento de Ciência da Computação
* Teoria e Aplicação de Grafos 2019/01
* 
* Aluno: Lucas Araújo Pena - 13/0056162
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<int>> Maximal;

//Cria lista de adjacência com os dados do arquivo "karate.gml"
void CriarListaAdjacencia(vector<int> grafo[]) {

	ifstream file;
	file.open("karate.gml");

	string line, sub;
	int j, s, t, len;
	int i = 0;

	//Lê o arquivo
	while (getline(file, line)) {
		len = line.length();
		
		if (len > 4) sub = line.substr(4,6);

		//Tratamento de dados para popular somente o que for importante.
		if (sub == "source") {
			i++;
			s = 0;

			for (j = 0; j != len; j++) {
				if ((line[j] >= 48) && (line[j] <= 57)) {
					if (s == 0) {
						s = (line[j] - 48);
					}

					else {
						s = (s * 10) + (line[j] - 48);
					}
				}
			}

		} //Source

		else if (sub == "target") {
			i++;
			t = 0;

			for (j = 0; j != len; j++) {
				if ((line[j] >= 48) && (line[j] <= 57)) {
					if (t == 0) {
						t = (line[j] - 48);
					}
					else {
						t = (t * 10) + (line[j] - 48);
					}
				}
			}

		} //Target

		sub = "0";
		if (i == 2) {
			i = 0;
			grafo[s].push_back(t);
			grafo[t].push_back(s);
		}
	}

	//Fecha o arquivo
	file.close();
}

//Esta função mostra na tela as listas de adjacências em ordem decrescente de grau.
void ImprimeLista(vector<int> grafo[], int vert) {
	vector<pair<int, int>> dual;

	int z = 0;

	for (int i = 1; i < vert; i++) {
		z = grafo[i].size();
		dual.push_back(pair<int, int>(i,z));
		z = 0;
	}

	sort(dual.begin(), dual.end(), [](auto &a, auto &b) {
		return a.second > b.second;
	});

	cout << endl << "Vertices de maior grau em ordem decrescente: " << endl;

	for (int w = 0; w < vert -1; ++w) {
		cout << "\n Lista de adjacencia do vertice: id " << dual[w].first;
		for (int j : grafo[dual[w].first]) {
			cout << " -> " << j;
		}

		cout << endl;
	}
}

// Esta função aplica o algoritmo de Bron-Kerbosch no grafo.
void BronKerbosch(vector<int> grafo[], vector<int> R, vector<int> P, vector<int> X) {
	if (P.empty() && X.empty()) {
		Maximal.push_back(R);
	}

	vector<int> P2 = P;

	for (int i : P2) {
		vector<int> intP = {}, intX = {};

		for (int j : grafo[i]) {
			for (int k : P){
				if (j == k) {
					intP.push_back(j);
				}
			}

			for (int l : X) {
				if (j == l) {
					intX.push_back(j);
				}
			}
		}

		vector<int> R2 = R;
		R2.push_back(i);
		BronKerbosch(grafo, R2, intP, intX);
		P.erase(remove(P.begin(), P.end(), i), P.end());
		X.push_back(i);

	}
}

//Esta função mostra na tela o clique maximal e um clique maximo diferente.
void ImprimeMaximal(vector<int> grafo[]) {
	sort(Maximal.begin(), Maximal.end(), [](auto &a, auto &b) {
		return a.size() > b.size();
	});

	cout << endl;
	cout << "Clique Maximal: ";

	for (int i : Maximal[0]) {
		cout << i << " ";
	}

	cout << endl << endl;
	cout << "Clique maximo diferente do Maximal: ";

	for (int j : Maximal[1]) {
		cout << j << " ";
	}

	cout << endl << endl;

}

//Esta função pausa o terminal. 
void Pause() {
	cout << "\n\n Pressione enter para fechar o programa...\n" << endl;
	std::cin.get();
}

int main() {
	//Número de vértices do grafo.
	int vert = 35;

	//Lista de adjacência
	vector<int> grafo[35];

	//Vetores para o algoritmo de Bron-Kerbosch
	vector<int> R, P, X;

	//Cria a lista de adjacencia apartir do grafo
	CriarListaAdjacencia(grafo);

	//Imprime na tela a lista 
	ImprimeLista(grafo, vert);


	for (int i = 1; i < vert; i++) {
		P.push_back(i);
	}

	//Realiza o algoritmo de Bron-Kerboesch no grafo
	BronKerbosch(grafo, R, P, X);

	ImprimeMaximal(grafo);

	Pause();

	return 0;
}