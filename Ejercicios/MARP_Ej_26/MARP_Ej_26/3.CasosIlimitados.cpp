#include <iostream>
#include <fstream>
#include "DigrafoValorado.h"
#include <limits>
#include "IndexPQ.h"

using namespace std;

class ResuelveRepartos {
private:
	const int INF = std::numeric_limits<int>::max();
	int origen;
	std::vector<int> dist;
	//std::vector<AristaDirigida<int>> ulti;
	IndexPQ<int> pq;

	void relajar(AristaDirigida<int> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor(); //ulti[w] = a;
			pq.update(w, dist[w]);
		}
	}

public:
	ResuelveRepartos(DigrafoValorado<int> const& g, int origen): origen(origen), dist(g.V(), INF), 
		/*ulti(g.V()),*/ pq(g.V()) {
		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; 
			pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}

	int devuelveDistancia(int pos) { return dist[pos]; }
	bool hayCamino(int v) const { return dist[v] != INF; }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int n, c;
	std::cin >> n >> c;

	if (!std::cin)  // fin de la entrada
		return false;

	DigrafoValorado<int> g(n);
	DigrafoValorado<int> traspuestoG(n);

	int v1, v2, esfuerzo;
	for (int i = 0; i < c; i++) {
		cin >> v1 >> v2 >> esfuerzo;
		g.ponArista({ v1 - 1, v2 - 1, esfuerzo });
		traspuestoG.ponArista({ v2 - 1, v1 - 1, esfuerzo });
	}

	int origen, numRepartos;
	cin >> origen >> numRepartos;
	origen--;

	int esfuerzoTotal = 0, posReparto;
	bool correcto = true;

	ResuelveRepartos origenDestino(g, origen);
	ResuelveRepartos destinoOrigen(traspuestoG, origen);

	for (int i = 0; i < numRepartos; i++) {
		//Resolver
		cin >> posReparto;
		if (!correcto)continue;

		if (origenDestino.hayCamino(posReparto - 1) && destinoOrigen.hayCamino(posReparto-1))
			esfuerzoTotal += origenDestino.devuelveDistancia(posReparto - 1) + destinoOrigen.devuelveDistancia(posReparto-1);
		
		else correcto = false;
	}

	if (!correcto)cout << "Imposible\n";
	else cout << esfuerzoTotal << "\n";

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
