
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
#include <limits>

template <typename Valor>
class Dijkstra {
private:
	const Valor INF = std::numeric_limits<Valor>::max();
	int origen;
	std::vector<Valor> dist;
	IndexPQ<Valor> pq;
	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor();
			pq.update(w, dist[w]);
		}
	}

public:
	Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
		dist(g.V(), INF), pq(g.V()) {
		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}

	bool hayCamino(int v) const { return dist[v] != INF; }
	Valor distancia(int v) const { return dist[v]; }

};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	int v;
	std::cin >> v;

	if (v == 0)return false;
	std::vector<int> tiemposCarga(v, 0);

	int cargaPag;
	for (int i = 0; i < v; i++) {
		std::cin >> cargaPag;
		tiemposCarga[i] = cargaPag;
	}
	
	
	DigrafoValorado<int> g(v);
	int a, v1, v2, tiempo;
	std::cin >> a;

	for (int i = 0; i < a; i++) {
		std::cin >> v1 >> v2 >> tiempo;
		g.ponArista({ v1 - 1,v2 - 1, tiemposCarga[v1-1] + tiempo });
	}
	
	// escribir sol
	Dijkstra<int> solucion(g, 0);
	if (solucion.hayCamino(v-1)) {
		std::cout << solucion.distancia(v - 1) + tiemposCarga[v - 1] << "\n";
	}
	else std::cout << "IMPOSIBLE\n";


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
