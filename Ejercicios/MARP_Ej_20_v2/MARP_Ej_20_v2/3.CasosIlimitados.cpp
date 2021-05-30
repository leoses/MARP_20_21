//Leire Osés Sánchez

#include <iostream>
#include <fstream>
#include "ConjuntosDisjuntos.h"
#include <string>

using namespace std;

class Manchas {
private: 
	std::vector<pair<int, int>> direcciones = { {-1,-1},{-1,0}, {-1,1}, {0,-1},{0,1}, {1,-1},{1,0},{1,1} };
	int tamManchaMax = 0;
	bool hayMancha = false;
	ConjuntosDisjuntos manchas;
	int f, c;

	bool coordenadasValidas(int i, int j) {
		return i >= 0 && i < f && j >= 0 && j < c;
	}

public:
	Manchas(vector<vector<bool>> const& tablero):f(tablero.size()), c(tablero[0].size()),
		manchas(tablero.size()* tablero[0].size()) {
		for (int i = 0; i < tablero.size(); i++) {
			for (int j = 0; j < tablero[i].size(); j++) {
				if (tablero[i][j]) {
					hayMancha = true;
					
					for (int k = 0; k < direcciones.size(); k++) {
						int newi = i + direcciones[k].first;
						int newj = j + direcciones[k].second;
						if (coordenadasValidas(newi, newj) && tablero[newi][newj]) {
							manchas.unir(i * c + j, newi * c + newj);
						}
					}

					int cardinal = manchas.cardinal(i * c + j);
					if (cardinal > tamManchaMax)tamManchaMax = cardinal;

				}
			}
		}
	}

	bool hayManchasPetroleo() { return hayMancha; }
	int devuelveTamManchaMax() { return tamManchaMax; }

	void nuevaMancha(std::vector<vector<bool>> const& tablero,int i, int j){
		for (int k = 0; k < direcciones.size(); k++) {
			int newi = i + direcciones[k].first;
			int newj = j + direcciones[k].second;
			if (coordenadasValidas(newi, newj) && tablero[newi][newj]) {
				manchas.unir(i * c + j, newi * c + newj);
			}

		}

		int cardinal = manchas.cardinal(i * c + j);
		if (cardinal > tamManchaMax)tamManchaMax = cardinal;
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
	vector<vector<bool>> tablero(f ,std::vector<bool>(c, false)); 
	char aux = cin.get();
	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j) {
			if (cin.get() == '#') {
				tablero[i][j] = true;
			}
		}
		aux = cin.get();
	}

	Manchas m(tablero);

	if (m.hayManchasPetroleo())std::cout << m.devuelveTamManchaMax() << " ";
	else std::cout << 0 << " ";

	int nuevasFotos, i, j;
	std::cin >> nuevasFotos;

	for (int k = 0; k < nuevasFotos; k++) {
		std::cin >> i >> j;
		i--; j--;
		tablero[i][j] = true;
		m.nuevaMancha(tablero, i, j);
		std::cout << m.devuelveTamManchaMax() << " ";
	}

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	/*std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());*/
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	/*std::cin.rdbuf(cinbuf);
	system("PAUSE");*/
#endif
	return 0;
}
