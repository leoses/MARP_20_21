
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int resuelveProblema(Matriz<int>& sol, vector<int> const& cubos , int i, int j) {
	if (i > j)return 0;
	else if (sol[i][j] != 0) return sol[i][j]; //Subproblema resuelto
	else if (i == j) sol[i][j] = cubos[i]; // solo queda un cubo
	else {
		int modIzq1=0, modDcha1=0;
		if (cubos[i + 1] > cubos[j]) modIzq1 = 1;
		else modDcha1 = 1;

		int modIzq2 = 0, modDcha2 = 0;
		if (cubos[i] > cubos[j-1]) modIzq2 = 1;
		else modDcha2 = 1;

		sol[i][j] = max(resuelveProblema(sol, cubos, i + 1 + modIzq1, j - modDcha1) + cubos[i], resuelveProblema(sol, cubos, i + modIzq2, j - 1 - modDcha2) + cubos[j]);

	}

	return sol[i][j];
}

bool resuelveCaso() {

	// leer los datos de la entrada
	int c;
	cin >> c;
	if (c == 0) return false;

	vector<int> cubos;
	int cubo;
	for (int i = 0; i < c; i++) {
		cin >> cubo;
		cubos.push_back(cubo);
	}

	Matriz<int> formas(cubos.size(), cubos.size(), 0);

	// resolver el caso posiblemente llamando a otras funciones
	// escribir la solución
	cout << resuelveProblema(formas, cubos, 0, cubos.size() - 1)<< "\n";

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

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
