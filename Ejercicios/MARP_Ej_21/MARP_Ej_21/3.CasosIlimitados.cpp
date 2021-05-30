
//Leire Osés Sánchez

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"


class ResuelveCamion {
private:
	std::vector<bool> visitados;

	void dfs(GrafoValorado<int> const& G, int v, int umbral) {
		visitados[v] = true;
		for (auto a : G.ady(v)) {
			if (a.valor() >= umbral) {
				int w = a.otro(v);
				if (!visitados[w])
					dfs(G, w, umbral);
			}
		}
	}

public:
	ResuelveCamion(GrafoValorado<int> const& g, int ini, int fin, int valor) : visitados(g.V(), false) {
		dfs(g, ini, valor);

		if (visitados[fin]) std::cout << "SI\n";
		else std::cout << "NO\n";
	}

};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada

	int v, a;
	std::cin >> v >> a;

	if (!std::cin)  // fin de la entrada
		return false;

	//Construccion del grafo
	GrafoValorado<int> g(v);
	int v1, v2, tam;
	for (int i = 0; i < a; i++) {
		std::cin >> v1 >> v2 >> tam;
		g.ponArista({ v1 - 1, v2 - 1, tam });
	}

	int k;
	std::cin >> k;

	for (int i = 0; i < k; i++) {
		std::cin >> v1 >> v2 >> tam;
		ResuelveCamion solucion(g, v1 - 1, v2 - 1, tam); //Procesa y escribe la solucion
	}

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
