#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

class Manchas {
private:
	int f, c;
	vector<vector<bool>> visitados;
	int maxManchasJuntas = 0;
	int numManchas = 0;

	struct Par {
		int f;
		int c;
	};

	const vector<Par> direcciones = { {1,0},{0,1},{-1,0},{0,-1} };

	bool coordenadasValidas(int i, int j) {
		return 0 <= i && i < f && 0 <= j && j < c;
	}

public:
	Manchas(vector<string> const& tablero) : f(tablero.size()), c(tablero[0].size()), visitados(f, vector<bool>(c, false)) {
		for (int i = 0; i < f; i++) {
			for (int j = 0; j < c; j++) {
				if (!visitados[i][j] && tablero[i].at(j) == '#') {
					numManchas++;//nueva mancha encontrada
					int tamanoMancha = dfs(tablero, i, j); //comprobamos tamaño mancha
					if (tamanoMancha > maxManchasJuntas)maxManchasJuntas = tamanoMancha; // si es mayor que el que tenemos registrado lo guardamos
				}
			}
		}

		cout << numManchas << " " << maxManchasJuntas << "\n";
	}

	int dfs(vector<string> const& tablero, int i, int j) {
		visitados[i][j] = true;
		int tam = 1;
		for (Par c : direcciones) {
			if (coordenadasValidas(i + c.f, j + c.c) && !visitados[i + c.f][j + c.c] && tablero[i + c.f].at(j + c.c) == '#') {
				tam += dfs(tablero, i + c.f, j + c.c);
			}
		}

		return tam;
	}
};
// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int f, c;
	std::cin >> f >> c;

	if (!std::cin)  // fin de la entrada
		return false;

	//Leemos el tablero
	vector<string> tablero(f);
	string aux;
	for (int i = 0; i < f; i++) {
		cin >> aux;
		tablero[i] = aux;
	}

	//La constructora de manchas resuelve
	Manchas m(tablero);

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
