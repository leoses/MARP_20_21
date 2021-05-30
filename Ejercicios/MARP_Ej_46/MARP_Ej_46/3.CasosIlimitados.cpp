
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
constexpr int INFINITO = 1000000000;
struct Moneda {
	int tipo;
	int num;
};

int resuelve(vector<int>& C, vector<Moneda> const& monedas, int tipos, int dinero) {
	C[0] = 0;
	for (int i = 1; i <= tipos; i++) {
		for (int j = dinero; j >= 1; j--) {
			int v = INFINITO;
			int maxMonedas = min(monedas[i - 1].num, j / monedas[i - 1].tipo);

			for (int k = 0; k <= maxMonedas; k++) {
				v = min(v, C[j - k * monedas[i - 1].tipo] + k);
			}
			C[j] = v;
		}
	}
	return C[dinero];
}

bool resuelveCaso() {

	// leer los datos de la entrada
	int tipos;
	cin >> tipos;

	if (!std::cin)  // fin de la entrada
		return false;

	int aux;
	vector<Moneda> monedas;
	for (int i = 0; i < tipos; i++) {
		cin >> aux;
		monedas.push_back({ aux, 0 });
	}
	for (int i = 0; i < tipos; i++) {
		cin >> aux;
		monedas[i].num = aux;
	}

	int dinero;
	cin >> dinero;

	// resolver el caso posiblemente llamando a otras funciones
	vector<int> C(dinero + 1, INFINITO);
	int min = resuelve(C, monedas, tipos, dinero);

	if (min != INFINITO)cout << "SI " << min << "\n";
	else cout << "NO\n";


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
