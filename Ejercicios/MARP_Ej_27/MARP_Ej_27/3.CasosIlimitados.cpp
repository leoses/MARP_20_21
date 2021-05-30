#include <iostream>
#include <fstream>
#include <vector>

int resolver(std::vector<int>const& distanciasAgujeros, int longCinta) {

	int cintasNecesarias = 0;
	int iniPosCinta = -1;
	for (int i = 0; i < distanciasAgujeros.size(); i++) {
		//Añadimos nueva cinta
		if (iniPosCinta < 0 ||  longCinta < distanciasAgujeros[i]-iniPosCinta) {
			cintasNecesarias++;
			iniPosCinta = distanciasAgujeros[i];
		}
	}

	return cintasNecesarias;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int agujeros, longCinta;
	std::cin >> agujeros >> longCinta;

	if (!std::cin)  // fin de la entrada
		return false;

	int pos;
	std::vector<int> posAgujeros(agujeros, 0);
	for (int i = 0; i < agujeros; i++) {
		std::cin >> pos;
		posAgujeros[i] = pos;
	}

	// escribir sol
	std::cout << resolver(posAgujeros, longCinta) << "\n";

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
