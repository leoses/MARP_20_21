
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


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CaminoMasCorto {
private:
	int origen;
	int destino;
	vector<bool> visitados;
	vector<int> distancia;

	void bfs(DigrafoValorado<int> const& g) {
		distancia[origen] = 0;
		visitados[origen] = true;
		queue<int> cola;
		cola.push(origen);

		while (!cola.empty()) {
			int v = cola.front();
			if (v == destino) return;
			cola.pop();

			for (auto w : g.ady(v)) {
				if (!visitados[w.hasta()]) {
					visitados[w.hasta()] = true;
					distancia[w.hasta()] = distancia[w.desde()] + 1;
					cola.push(w.hasta());
				}
			}
		}

	}
public:
	CaminoMasCorto(DigrafoValorado<int> const& g, int origen_, int destino_): visitados(g.V(), false), distancia(g.V(), 0),
	origen(origen_), destino(destino_){
		bfs(g);
	}

	bool hayCamino() { return visitados[destino]; }

	int menorDistancia() { return distancia[destino]; }
};

class CaminoMenosPeso {
private:
	const int INF = INT_MAX;
	int origen;
	int destino;
	std::vector<int> dist;
	vector<int> numAristas;
	IndexPQ<int> pq;
	void relajar(AristaDirigida<int> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor();
			numAristas[w] = numAristas[v] + 1;
			pq.update(w, dist[w]);
		}
		else if (dist[w] == dist[v] + a.valor() && numAristas[w] > numAristas[v] + 1) { 
			numAristas[w]= numAristas[v] + 1;
		}
	}
public:
	CaminoMenosPeso(DigrafoValorado<int> const& g, int orig, int dest) : origen(orig), destino(dest), 
		dist(g.V(), INF), pq(g.V()), numAristas(g.V(), 0) {
		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty() && pq.top().elem != destino) {
			int v = pq.top().elem; 
			pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}

	bool hayCamino(int v) const { return dist[v] != INF; }
	int distancia(int v) const { return dist[v]; }
	int aristasHasta() const { return numAristas[destino]; }
};
	
bool resuelveCaso() {

	// leer los datos de la entrada
	int n, c;
	cin >> n >> c;
	if (!std::cin)  // fin de la entrada
		return false;

	DigrafoValorado<int> g(n);

	int v1, v2, valor;
	for (int i = 0; i < c; i++) {
		cin >> v1 >> v2>> valor;
		g.ponArista({ v1 - 1, v2 - 1, valor });
		g.ponArista({ v2 - 1, v1 - 1, valor });
	}

	int K;
	cin >> K;
	int ini, fin;
	for (int i = 0; i < K; i++) {
		cin >> ini >> fin;
		CaminoMasCorto haySol(g, ini - 1, fin - 1);
		if (haySol.hayCamino()) {
			CaminoMenosPeso mejorC(g, ini- 1, fin - 1);
			cout << mejorC.distancia(fin - 1) << " ";

			if (haySol.menorDistancia() == mejorC.aristasHasta())cout << "SI\n";
			else cout << "NO\n";
		}
		else cout << "SIN CAMINO\n";
	}

	cout << "---\n";

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
