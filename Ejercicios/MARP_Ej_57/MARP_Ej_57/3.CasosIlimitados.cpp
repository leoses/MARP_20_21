
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Matriz.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int resuelveProblema(Matriz<int> & formas, vector<int> const& bizcocho, int i, int j) {
	if (i > j)return 0;
	else if (formas[i][j] != -1) return formas[i][j];
	else if (bizcocho[i] == bizcocho[j] && bizcocho[i] != 0) formas[i][j] = resuelveProblema(formas, bizcocho, i+1, j-1) + 1;
	else formas[i][j] = max(max(resuelveProblema(formas, bizcocho, i + 2, j), resuelveProblema(formas, bizcocho, i, j - 2)), resuelveProblema(formas, bizcocho, i + 1, j - 1));

	return formas[i][j];
}

bool resuelveCaso() {

	// leer los datos de la entrada
	int n;
	cin >> n;
	if (!std::cin)return false;

	vector<int> bizcocho;
	int rodaja;	
	for (int i = 0; i < n; i++) {
		cin >> rodaja;
		bizcocho.push_back(rodaja);
	}
	Matriz<int> formas(bizcocho.size(), bizcocho.size(), -1);

	// resolver el caso posiblemente llamando a otras funciones
	// escribir la solución
	cout << resuelveProblema(formas, bizcocho, 0, bizcocho.size() - 1)<< "\n";

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
