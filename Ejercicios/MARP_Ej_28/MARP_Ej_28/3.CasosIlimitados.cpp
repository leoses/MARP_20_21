#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int resolver(std::vector<int>const& enemigos, std::vector<int>const& aliados) {
	int ganados = 0;
	int minEnemigos = 0, minAliados = 0;
	while (minEnemigos < enemigos.size() && minAliados < aliados.size()) {
		if (enemigos[minEnemigos] <= aliados[minAliados]) {
			ganados++;
			minEnemigos++;
		}
		minAliados++;
	}

	return ganados;

}
// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int ciudades;
	std::cin >> ciudades;
	if (!std::cin)  // fin de la entrada
		return false;

	std::vector<int>enemigos;
	std::vector<int>aliados;

	int tropa;

	for (int i = 0; i < ciudades; i++) {
		std::cin >> tropa;
		enemigos.push_back(tropa);
	}

	for (int i = 0; i < ciudades; i++) {
		std::cin >> tropa;
		aliados.push_back(tropa);
	}

	//Ordenacion de elementos (2*nlog(n)) siendo n el numero de ciudades
	std::sort(enemigos.begin(), enemigos.end());
	std::sort(aliados.begin(), aliados.end());

	std::cout << resolver(enemigos, aliados)<<"\n"; //coste O(n)

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
