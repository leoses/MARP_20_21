//Leire Osés Sánchez

#include <iostream>
#include <fstream>
#include "Digrafo.h"
#include <vector>
#include <deque>

class OrdenandoTareas {
private:
	bool hayCiclo = false;
	std::vector<bool> visitados;
	std::vector<bool> apilado;
	std::deque<int> _orden;
	int tareasHechas = 0;
	int numTareas = 0;


	//Esto se puede hacer solo si no hay ciclos
	void dfs(Digrafo const& g, int v) {
		visitados[v] = true;
		apilado[v] = true;
		tareasHechas++;
		for (int i : g.ady(v)) {
			if (hayCiclo)return;
			if (!visitados[i]) dfs(g, i); //Si no esta visitado, llamamos a dfs()
			else if (apilado[i]) hayCiclo = true; //Si esta apilado y visitado hay ciclo
		}

		//Se desapila
		apilado[v] = false;
		//lo añadimos a la ordenacion
		_orden.push_front(v);

	}

public:
	OrdenandoTareas(Digrafo const& g): visitados(g.V(), false), apilado(g.V(), false), numTareas(g.V()){
		for (int i = 0; i < g.V(); i++) {
			if (!hayCiclo && !visitados[i]) dfs(g, i);
		}
	}

	void escribeSol() {
		if (numTareas == tareasHechas && !hayCiclo) escribeOrden();
		else std::cout << "Imposible\n";
	}

	void escribeOrden() {
		for (int i : _orden)std::cout << i + 1 << " ";
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

	//Creamos el grafo de n vertices
	Digrafo g(n);
	int a, b;
	for (int i = 0; i < m; i++) {
		std::cin >> a >> b;
		g.ponArista(a - 1, b - 1);
	}

	OrdenandoTareas solucion(g);

	solucion.escribeSol();

	// escribir sol

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
