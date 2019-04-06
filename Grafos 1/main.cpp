/*
Universidade de Brasília
Departamento de Ciência da Computação
Teoria e Aplicação de Grafos 2019/01
Aluno: Lucas Araújo Pena - 13/0056162

Códigos consultados:
http://bit.ly/2HTIGLH
http://bit.ly/2uIYQ1B

*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<int>> Maximal;

//Cria lista de adjacencia com os dados do arquivo "karate.gml"
void CriarListaAdjacencia(vector<int> grafo[]) {

	ifstream file;
	file.open("karate.gml");

	string line, sub;
	int j, s, t, len;
	int i = 0;

	//Le o arquivo
	while (getline(file, line)) {
		len = line.length();

		if (len > 4) sub = line.substr(4, 6);

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

//Esta funcao mostra na tela as listas de adjacencias em ordem decrescente de grau.
void ImprimeLista(vector<int> grafo[], int vert) {
	vector<pair<int, int>> dual;

	int z = 0;
	int tmp = 0;

	for (int i = 1; i < vert; i++) {
		z = grafo[i].size();
		dual.push_back(pair<int, int>(i, z));
		z = 0;
	}

	sort(dual.begin(), dual.end(), [](auto &a, auto &b) {
		return a.second > b.second;
	});

	cout << endl << "Vertices de maior grau em ordem decrescente: " << endl;

	for (int w = 0; w < vert - 1; ++w) {
		for (int j : grafo[dual[w].first]) {
			tmp++;
		}
		cout << "\nGrau do vertice " << dual[w].first << ": " << tmp;
		cout << endl;
		tmp = 0;
	}
}

// Esta funcao aplica o algoritmo de Bron-Kerbosch no grafo.
void BronKerbosch(vector<int> grafo[], vector<int> R, vector<int> P, vector<int> X) {
	if (P.empty() && X.empty()) {
		Maximal.push_back(R);
	}

	vector<int> P2 = P;

	for (int i : P2) {
		vector<int> intP = {}, intX = {};

		for (int j : grafo[i]) {
			for (int k : P) {
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

//Esta funcao mostra na tela o clique maximal e um clique maximo diferente.
void ImprimeMaximal(vector<int> grafo[]) {
	sort(Maximal.begin(), Maximal.end(), [](auto &a, auto &b) {
		return a.size() > b.size();
	});

	cout << endl;
	cout << "\n\nCliques Maximais:\n ";


	for (int m = 0; m < Maximal.size(); m++) {
		int j = 0;

		for (int i : Maximal[m]) {

			if (j == 0) {
				cout << i;
				j++;
			}
			else {
				cout << " -> " << i;
			}
		}

		cout << endl;
	}

	cout << endl << endl;

}

//Funcao para calcular o Coeficiente de aglomeracao
void CoeficienteAglomeracao(vector<int> grafo[]) {

	//grafo;
	//int triangulos = 0;

	/*for (int i = 0; i < len; i++) {

	}*/
}

//Esta funcao pausa o terminal. 
void Pause() {
	cout << "\n\nPressione enter para fechar o programa...\n" << endl;
	std::cin.get();
}

int main() {
	//Numero de vertices do grafo.
	int vert = 35;

	//Lista de adjacencia
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

	//Mostra os Maximais na tela
	ImprimeMaximal(grafo);

	//Calcula e mostra na tela os coeficientes calculados.
	CoeficienteAglomeracao(grafo);

	//Pausa a aplicacao para a verificacao dos dados.
	Pause();

	return 0;
}