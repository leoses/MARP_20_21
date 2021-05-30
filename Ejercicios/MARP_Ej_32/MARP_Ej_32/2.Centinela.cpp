#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

struct Intervalo {
	int ini, fin;
};

bool operator<(Intervalo const& a, Intervalo const& b) {
	return a.ini < b.ini;
}

bool operator>(Intervalo const& a, Intervalo const& b) {
	return a.fin < b.fin;
}

bool comprendidoEntre(int elem, Intervalo intervalo) {
	return intervalo.ini <= elem && elem < intervalo.fin;
}


void resolver(vector<Intervalo> const& datos, int c, int f) {
	int tareas = 0;
	int i = 0;

	int posActual = c;
	bool incorrecto = false;

	while (!incorrecto && posActual < f) {
		int max = -1;
		while (i < datos.size() && datos[i].ini <= posActual) {
			if (datos[i].fin > max) max = datos[i].fin;
			i++;
		}

		if (max == -1) incorrecto = true;
		else {
			tareas++;
			posActual = max;
		}
	}
	

	if (posActual < f || incorrecto) cout << "Imposible\n";
	else cout << tareas << "\n";
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int c, f, n;
	cin >> c >> f >> n;
	if (c == 0 && f == 0 && n == 0) return false;

	int ini, fin;
	vector<Intervalo> vIntervalos;

	for (int i = 0; i < n; i++) {
		cin >> ini >> fin;
		vIntervalos.push_back({ ini, fin });
	}

	sort(vIntervalos.begin(), vIntervalos.end());

	resolver(vIntervalos, c, f);

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
