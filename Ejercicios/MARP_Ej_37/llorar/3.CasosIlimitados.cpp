
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include "EnterosInf.h"
#include "Matriz.h"


using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
//Solucion resolver(Datos datos) {
//   ...
//}

int devuelveMax(vector<int>const& filaAnt, int j) {
	int max = filaAnt[j];
	if (j - 1 >= 0 && filaAnt[j-1]>max) max = filaAnt[j - 1];
	if (j + 1 < filaAnt.size()&& filaAnt[j + 1] > max)max = filaAnt[j + 1];

	return max;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada

	int n;
	cin >> n;
	if (!std::cin)  // fin de la entrada
		return false;

	Matriz<int> tablero(n, n, 0);
	int aux;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> aux;
			tablero[i][j] = aux;
		}
	}

	vector<int> filaAnt;
	vector<int> filaActual(n,0);

	for (int i = 0; i < n; i++) {
		filaAnt.push_back(tablero[0][i]);
	}

	for (int i = 1 ; i < n; i++) {
		for (int j = 0; j < n; j++) {
			filaActual[j] =  devuelveMax(filaAnt, j) + tablero[i][j];
		}
		filaAnt = filaActual;
	}

	int indiceMax = 0;
	for (int i = 1; i < n; i++) {
		if (filaActual[indiceMax] < filaActual[i])indiceMax = i;
	}

	cout << filaActual[indiceMax] << " " << indiceMax+1 << "\n";

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
