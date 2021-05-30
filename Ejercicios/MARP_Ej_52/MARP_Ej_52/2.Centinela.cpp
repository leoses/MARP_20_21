
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
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

bool resuelveCaso() {

	// leer los datos de la entrada
	int N;
	cin >> N;
	if (N == 0) return false;
	priority_queue<int64_t, vector<int64_t>, greater<int64_t>> cola;

	int64_t num;
	for (int i = 0; i < N; i++) {
		cin >> num;
		cola.push(num);
	}

	//Resolver
	int64_t total = 0;
	int64_t elem1, elem2;
	while (cola.size() > 1) {
		elem1 = cola.top(); cola.pop();
		elem2 = cola.top(); cola.pop();
		total += elem1 + elem2;
		cola.push(elem1 + elem2);
	}

	//Escribir la solucion
	cout<< total<< "\n";

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
