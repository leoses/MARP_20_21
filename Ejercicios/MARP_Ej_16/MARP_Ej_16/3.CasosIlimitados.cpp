
// Leire Osés Sánchez

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

class MaquinaCalculadora {
private:
	const int MAXNUMBER = 10000;
	const int NOTVISITED = -1;

	int operacionesNecesarias = 0;

	int bfs(int ini, int fin) {
		if (ini == fin) return 0;//Si el final es el mismo que principio la distancia es 0
		std::vector<int> distancia(MAXNUMBER, NOTVISITED);
		distancia[ini] = 0;

		std::queue<int> cola; cola.push(ini);

		while (!cola.empty()) {
			int vertex = cola.front();
			cola.pop();
			std::vector<int> ady = { (vertex + 1) % MAXNUMBER,  (vertex * 2) % MAXNUMBER, vertex/3 };
			for (int i : ady) {
				if (distancia[i] == NOTVISITED) {
					distancia[i] = distancia[vertex] + 1;
					if (i == fin) return distancia[i];
					else cola.push(i);
				}
			}
		}
	}

	//Correcto tb pero menos eficiente
	//const std::vector<int> adyacente(int num) {
	//	std::vector<int> ady;
	//	ady.resize(3);

	//	ady[0] = (num + 1) % MAXNUMBER;
	//	ady[1] = (num * 2) % MAXNUMBER;
	//	ady[2] = (num / 3);

	//	return ady;
	//}

public:
	MaquinaCalculadora(int ini, int fin) { operacionesNecesarias = bfs(ini, fin); }

	int resultado() { return operacionesNecesarias; }
};


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada

	int ini, fin;

	std::cin >> ini >> fin;

	if (!std::cin)  // fin de la entrada
		return false;

	//Solucion
	MaquinaCalculadora m(ini, fin);

	// escribir sol
	std::cout << m.resultado() << "\n";

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
