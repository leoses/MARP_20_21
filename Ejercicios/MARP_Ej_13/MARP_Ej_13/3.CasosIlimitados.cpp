
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class colocarGuardias {
private:
	vector<bool>visitados;
	int conjunto1 = 0;
	int conjunto2 = 0;

	int minGuardias = 0;

	vector<int> distancia;
	vector<bool> conjunto;//1 true falso 2
	queue<int> cola;
	bool k = true;

	bool bfs(Grafo const& g, int s) {
		std::queue<int> q;
		visitados[s] = true;
		conjunto[s] = true;
		conjunto1++;
		q.push(s);
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (int w : g.ady(v)) {
				if (!visitados[w]) {
					distancia[w] = distancia[v] + 1;
					if (distancia[w] % 2 == 0) {
						conjunto[w] = true;
						conjunto1++;
					}
					else {
						conjunto[w] = false;
						conjunto2++;
					}

					visitados[w] = true;
					q.push(w);
				}
				else {
					if (conjunto[w] == conjunto[v]) return false;
				}
			}
		}
		return true;
	}


public:
	colocarGuardias(Grafo const& g) : visitados(g.V(), false), conjunto(g.V()), distancia(g.V(), 0) {
		for (int i = 0; i < g.V() && k; ++i) {
			if (!visitados[i]) {
				if (!bfs(g, i)) {
					k = false;
				}
				else {
					minGuardias += min(conjunto1, conjunto2);
					conjunto1 = 0;
					conjunto2 = 0;
				}
			}
		}
	}

	bool esCorrecto() { return k; }
	int nGuardias() { return minGuardias; }
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int n, c;
	std::cin >> n >> c;
	if (!std::cin) return false;
	
	//Creamos grafo con n nodos
	Grafo g(n);
	int v1, v2;
	for (int i = 0; i < c; i++) {
		std::cin >> v1 >> v2;
		g.ponArista(v1 - 1, v2 - 1);
	}

	// resolver el caso posiblemente llamando a otras funciones
	colocarGuardias solucion(g);

	// escribir la solución
	if (solucion.esCorrecto())cout << solucion.nGuardias() << "\n";
	else cout << "IMPOSIBLE\n";

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
