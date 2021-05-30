
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include "Matriz.h"
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

const int INFINITO = INT_MAX;

bool resuelveCaso() {

	// leer los datos de la entrada
	int n, l;
	cin >> l >> n;

	if (n == 0 && l == 0)return false;

	vector<int> cortes;
	int corte;
	cortes.push_back(0);
	for (int i = 0; i < n; i++) {
		cin >> corte;
		cortes.push_back(corte);
	}
	cortes.push_back(l);

	n += 2;// 0 y l como extremos de la madera

	//i,j -> coste minimo de cortar desde i hasta j 
	//si j-2 < i significa que no hay que cortar porque no hay puntos de corte entre medias(ordenados creciente)
	Matriz<int> M(n, n, 0); 
	for (int d = 2; d < n ; ++d) {  //Cortar cuando haya al menos 3 puntos
		for (int i = 0; i < n - d; ++i) {
			int j = d + i;
			int mejor = INT_MAX;
			for (int m = i + 1; m < j; ++m) {
				mejor = min(mejor, M[i][m] + M[m][j]);
			}
			M[i][j] = mejor + 2 * (cortes[j] - cortes[i]);
		}
	}
	cout << M[0][n - 1] << '\n';


	// escribir la solución

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
