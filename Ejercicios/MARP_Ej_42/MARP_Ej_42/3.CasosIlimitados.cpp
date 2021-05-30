#include <iostream>
#include <fstream>
#include <unordered_map>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;

void Floyd(Matriz<EntInf> const& G, Matriz<EntInf>& C, Matriz<int>& A) {
	int V = G.numfils(); 
	C = G;
	A = Matriz<int>(V, V, -1);
	for (int i = 0; i < V; ++i) {
		for (int j = 0; j < V; ++j) {
			if (i != j && G[i][j] != Infinito)
				A[i][j] = i;
		}
	}

	for (int k = 0; k < V; ++k) {
		for (int i = 0; i < V; ++i) {
			for (int j = 0; j < V; ++j) {
				auto temp = C[i][k] + C[k][j];
				if (temp < C[i][j]) { 
					if (i == j)C[i][j] = 0;
					else C[i][j] = temp;
					A[i][j] = A[k][j];
				}
			}
		}
	}
}

#pragma region Pruebas
//bool esConexo(Matriz<int> const& A) {
//	bool conexo = true;
//	int i = 1;
//	while (conexo && i < A[0].size()) {
//		if (A[0][i] == -1)conexo = false;
//		i++;
//	}
//	return conexo;
//}
//
//EntInf maxConexiones(Matriz<EntInf> const& C) {
//	EntInf maxCon = 0;
//
//	for (int i = 0; i < C.numfils(); i++) {
//		for (int j = 0; j < C.numcols(); j++) {
//			if (i != j && maxCon < C[i][j])maxCon = C[i][j];
//		}
//	}
//	return maxCon;
//}
#pragma endregion

bool maxConexionesYConexo(Matriz<EntInf> const& C,EntInf & conn) {
	conn = 0;
	for (int i = 0; i < C.numfils(); i++) {
		for (int j = 0; j < C.numcols(); j++) {
			if (i != j && C[i][j] == Infinito) return false;
			else if (i != j && conn < C[i][j]) conn = C[i][j];
		}
	}
	return true;
}

bool resuelveCaso() {

	// leer los datos de la entrada
	int p, r;

	cin >> p >> r;

	if (!std::cin) return false;

	unordered_map<string, int> personas;
	Matriz<EntInf> grafo(p, p, Infinito);

	string p1, p2;
	int personasProc = 0;

	for (int i = 0; i < r; i++) {
		cin >> p1 >> p2;
		if (personas.count(p1) != 1) {
			personas[p1] = personasProc;
			personasProc++;
		}
		if (personas.count(p2) != 1) {
			personas[p2] = personasProc;
			personasProc++;
		}
		grafo[personas[p1]][personas[p2]] = 1;
		grafo[personas[p2]][personas[p1]] = 1;
	}

	Matriz<EntInf> C;
	Matriz<int> A;

	Floyd(grafo, C, A);

	//bool conexo = esConexo(A);
	EntInf conn;
	
	if (maxConexionesYConexo(C,conn))cout << conn << "\n";
	else cout << "DESCONECTADA\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	//std::ifstream in("casos.txt");
	//auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	//std::cin.rdbuf(cinbuf);
	//system("PAUSE");
#endif
	return 0;
}
