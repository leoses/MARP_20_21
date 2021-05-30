
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#include "Matriz.h"
#include <climits>

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

struct Cordel {
	int longitud;
	int coste;
};

struct Soluciones {
	int64_t minCuerdas;
	int64_t minCoste;
	int64_t numFormas;
};

const int64_t Infinito = 1000000000000000000;

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

	// leer los datos de la entrada
	int N, L;
	cin >> N >> L;
	if (!std::cin)  // fin de la entrada
		return false;

	vector<Cordel>cuerdas;

	int longitud, cost;
	for (int i = 0; i < N; i++) {
		cin >> longitud >> cost;
		cuerdas.push_back({ longitud, cost });
	}

	//Falta comprimir la matriz a un vector
	Matriz<Soluciones> tabla(N + 1, L + 1, { Infinito, Infinito, 0 });

	tabla[0][0].minCoste = 0;
	tabla[0][0].minCuerdas = 0;
	tabla[0][0].numFormas = 1;

	for (int i = 1; i <= N; ++i) {
		tabla[i][0].minCoste = 0;
		tabla[i][0].minCuerdas = 0;
		tabla[i][0].numFormas = 1;
		for (int j = L; j >= 0; --j) {
			if (j < cuerdas[i - 1].longitud) {
				tabla[i][j].minCoste = tabla[i - 1][j].minCoste;
				tabla[i][j].minCuerdas = tabla[i - 1][j].minCuerdas;
				tabla[i][j].numFormas = tabla[i - 1][j].numFormas;
			}
			else {
				tabla[i][j].minCuerdas = min(tabla[i - 1][j].minCuerdas, tabla[i - 1][j - cuerdas[i - 1].longitud].minCuerdas + 1);
				tabla[i][j].minCoste = min(tabla[i - 1][j].minCoste, tabla[i - 1][j - cuerdas[i - 1].longitud].minCoste + cuerdas[i - 1].coste);
				tabla[i][j].numFormas = tabla[i - 1][j].numFormas + tabla[i - 1][j - cuerdas[i - 1].longitud].numFormas;
			}
		}
	}

	if (tabla[N][L].minCuerdas != Infinito) 
		cout << "SI " << tabla[N][L].numFormas << " "<<tabla[N][L].minCuerdas << " " << tabla[N][L].minCoste << "\n";
	else cout << "NO\n";

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	/*std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());*/
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	//std::cin.rdbuf(cinbuf);
	//system("PAUSE");
#endif
	return 0;
}
