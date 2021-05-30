
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>

class Sumidero {
private:
	bool haySumidero = false;
	int posibleSumidero = -1;

public:
	Sumidero(std::vector<std::vector<bool>> const& grafo) {

		int u = 0, w = 1, siguiente = 2;

		while (u < grafo.size() && w < grafo.size()) {
			if (grafo[u][w]) {
				posibleSumidero = w;
				u = w;
			}
			else posibleSumidero = u;

			w = siguiente;
			siguiente++;
		}


		//Si posible sumidero es -1, significa que no ha entrado en el bucle while de arriba
		//y por lo tanto solo tiene un vértice -> Caso base, es sumidero
		if (posibleSumidero == -1 && grafo.size() == 1) {
			haySumidero = true;
			posibleSumidero = 0;
		}
		else if (posibleSumidero < grafo.size()) {
			int i = 0;
			for (; i < grafo.size(); i++) {
				if (i != posibleSumidero && !grafo[i][posibleSumidero]) break;
				else if (i != posibleSumidero && grafo[posibleSumidero][i])break;
			}

			if (i == grafo.size()) haySumidero = true;
		}
	}

	bool tieneSumidero() { return haySumidero; }
	int devuelveSumidero() { return posibleSumidero; }


};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int v, a;
	std::cin >> v >> a;

	if (!std::cin)return false;

	//Matriz de adyacencia
	std::vector<std::vector<bool>> grafo(v, std::vector<bool>(v, false));

	//Creacion de las aristas
	int v1, v2;
	for (int i = 0; i < a; i++) {
		std::cin >> v1 >> v2;
		grafo[v1][v2] = true;
	}

	Sumidero solucion(grafo);

	if (solucion.tieneSumidero())std::cout << "SI " << solucion.devuelveSumidero() << "\n";
	else std::cout << "NO\n";

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
