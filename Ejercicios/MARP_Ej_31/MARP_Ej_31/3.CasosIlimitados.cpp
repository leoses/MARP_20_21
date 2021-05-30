
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edificio {
	int ini, fin;
};

bool operator<(const Edificio a, const Edificio b) {
	return a.fin < b.fin;
}

bool inRange(const Edificio limits, int elem) {
	return elem >= limits.ini && elem < limits.fin;
}

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(vector<Edificio> const& datos) {
	int numTuneles = 0;
	int posUltTunel = -1;
	for (int i = 0; i < datos.size(); i++) {
		if (!inRange(datos[i], posUltTunel)) {
			numTuneles++;
			posUltTunel = datos[i].fin-1;
		}
	}

	return numTuneles;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int edificios;
	cin >> edificios;

	if (edificios == 0)  // fin de la entrada
		return false;

	vector<Edificio> vEdificios;
	int ini, fin;
	for(int i = 0; i < edificios; i++){
		cin >> ini >> fin;
		vEdificios.push_back({ ini, fin });
	}

	sort(vEdificios.begin(), vEdificios.end());

	cout << resolver(vEdificios)<< "\n";

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
