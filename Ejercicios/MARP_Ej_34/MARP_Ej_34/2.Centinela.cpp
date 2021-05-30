#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(vector <int>const& inicios, vector<int>const&finales) {
	int maxComp = 0, amigosRonda = -1, ini = 0, fin = 0;

	while (ini < inicios.size() && fin < finales.size()) {
		while (ini < inicios.size() &&  inicios[ini] < finales[fin]) {
			amigosRonda++;
			ini++;
		}

		fin++;
		if (amigosRonda > maxComp) maxComp = amigosRonda;
		amigosRonda--;
	}


	return maxComp;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int n;
	cin >> n;

	if (n == 0) return false;

	vector<int>inicios;
	vector<int>finales;

	int ini, fin;

	for (int i = 0; i < n; i++) {
		cin >> ini >> fin;
		inicios.push_back(ini);
		finales.push_back(fin);
	}
	sort(inicios.begin(), inicios.end());
	sort(finales.begin(), finales.end());

	cout << resolver(inicios, finales)<< "\n";

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
