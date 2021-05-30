
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <climits>
using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

class DijikstraIslas {
private:
	int origen;
	const int INF = INT_MAX;
	std::vector<int> dist;
	IndexPQ<int> pq;
	int N;

	void relajar(AristaDirigida<int> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor();
			pq.update(w, dist[w]);
		}
	}
public:
	DijikstraIslas(DigrafoValorado<int>const& g, int origen_): origen(origen_), dist(g.V(), INF), 
		pq(g.V()), N(g.V()){
			dist[origen] = 0;
			pq.push(origen, 0);
			while (!pq.empty()) {
				int v = pq.top().elem;
				pq.pop();
				for (auto a : g.ady(v))
					relajar(a);
			}
		
	}

	void EscribeSol() {
		int i = origen + 1;
		for (; i < N-1; i++) {
			cout << dist[i] << " ";
		}
		cout << dist[i] << "\n";
	}
};


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {

	// leer los datos de la entrada
	int N;
	cin >> N;
	if (!std::cin)  // fin de la entrada
		return false;

	DigrafoValorado<int> isla(N);
	int costeIsla;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			cin >> costeIsla;
			isla.ponArista({ i,j,costeIsla });
		}
	}

	// resolver el caso posiblemente llamando a otras funciones
	// escribir la solución
	for (int i = 0; i < N-1; i++) {
		DijikstraIslas sol(isla, i);
		sol.EscribeSol();
	}

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
