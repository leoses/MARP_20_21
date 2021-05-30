#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int resolver(vector<int> const& alturasEsquiadores, vector<int> const& tamanoEsquis) {
	int diferencia = 0;

	for (int i = 0; i < alturasEsquiadores.size(); i++) {
		int dif = alturasEsquiadores[i] - tamanoEsquis[i];

		if (dif < 0)dif = -dif;

		diferencia += dif;
	}

	return diferencia;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int n;
	cin >> n;
	if (n == 0)  // fin de la entrada
		return false;

	vector<int> alturasEsquiadores;
	vector <int> longitudEsquis;

	int dato;
	for (int i = 0; i < n; i++) {
		cin >> dato;
		alturasEsquiadores.push_back(dato);
	}

	for (int i = 0; i < n; i++) {
		cin >> dato;
		longitudEsquis.push_back(dato);
	}

	sort(alturasEsquiadores.begin(), alturasEsquiadores.end());
	sort(longitudEsquis.begin(), longitudEsquis.end());

	int sol = resolver(alturasEsquiadores, longitudEsquis);

	cout << sol << "\n";

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
