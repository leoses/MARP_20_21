
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>
#include "Grafo.h"



class GruposNoticias {
private:
	std::vector<bool> visitados;
	std::vector<int> conexiones;
	int V;

public:
	GruposNoticias(Grafo const& g) : visitados(g.V(), false), conexiones(g.V(), 1), V(g.V()) {
		calculaConexiones(g);
	}

	int dfs(Grafo const& g, int v, std::vector<int> & pos) {
		visitados[v] = true;
		int tam = 1;
		for (int w : g.ady(v)) {
			if (!visitados[w]) {
				pos.push_back(w);
				tam += dfs(g, w, pos);
			}
		}
		return tam;
	}

	void calculaConexiones(Grafo const& g) {
		for (int i = 0; i < V; i++) {
			if (!visitados[i]) {
				std::vector<int> pos;
				int nConexiones = dfs(g, i, pos);
				conexiones[i] = nConexiones;
				for (int j = 0; j < pos.size(); j++) {
					conexiones[pos[j]] = nConexiones;
				}
			}
		}
	}

	void printConexiones() {
		for (int i = 0; i < V; i++) {
			std::cout << conexiones[i] << " ";
		}
		std::cout << "\n";
	}
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int n, m;
	std::cin >> n >> m;

	if (!std::cin)  // fin de la entrada
		return false;

	Grafo g(n);

	for (int i = 0; i < m; i++) {
		int numPersonas;
		std::cin >> numPersonas;
		if (numPersonas <= 0)continue;

		int v1, v2;
		std::cin >> v1;
		for (int j = 0; j < numPersonas - 1; j++) {
			std::cin >> v2;
			g.ponArista(v1 - 1, v2 - 1);
			v1 = v2;
		}
	}

	GruposNoticias obj(g);

	obj.printConexiones();



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
