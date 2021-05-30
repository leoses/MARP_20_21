// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include "DigrafoValorado.h"
#include <limits>
#include "IndexPQ.h"

class resuelveCole {
private:
	const int INF = std::numeric_limits<int>::max();
	int origen_;
	std::vector<int> dist;
	std::vector<AristaDirigida<int>> ult;
	IndexPQ<int> pq;
	std::vector<int> formasAVertice;
	int numFormas = 0;

	void relajar(AristaDirigida<int> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor(); ult[w] = a;
			pq.update(w, dist[w]);
			formasAVertice[w] = formasAVertice[v];
		}
		else if (dist[w] == dist[v] + a.valor())formasAVertice[w] += formasAVertice[v];
	}

public:
	resuelveCole(DigrafoValorado<int> const& g, int origen = 0) : dist(g.V(),INF), ult(g.V()), pq(g.V()), origen_(origen), formasAVertice(g.V(), 0)
	{
		dist[origen] = 0;
		formasAVertice[origen] = 1;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem;
			pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}

		std::cout << formasAVertice[g.V()-1] << "\n";
	}

};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int n,c;
	std::cin >> n >> c;

	if (!std::cin)  // fin de la entrada
		return false;

	DigrafoValorado<int> g(n);

	int v1, v2, valor;

	for (int i = 0; i < c; i++) {
		std::cin >> v1 >> v2 >> valor;
		g.ponArista({v1 - 1, v2 - 1, valor});
		g.ponArista({ v2 - 1, v1 - 1, valor });

	}

	// escribir sol
	resuelveCole solucion(g);

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
