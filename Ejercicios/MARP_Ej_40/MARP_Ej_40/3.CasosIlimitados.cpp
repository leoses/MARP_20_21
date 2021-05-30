#include <iostream>
#include <fstream>
#include <string>
#include "Matriz.h"

using namespace std;


int palindromo_rec(string const& palabra, int i, int j, Matriz<int>& P) {
	int& res = P[i][j];
	if (res == -1) {
		if (i > j) res = 0;
		else if (i == j) res = 1;
		else if (palabra[i] == palabra[j])
			res = palindromo_rec(palabra, i + 1, j - 1, P) + 2;
		else
			res = max(palindromo_rec(palabra, i + 1, j, P),
				palindromo_rec(palabra, i, j - 1, P));
	}
	return res;
}

void reconstruir(string const& palabra, Matriz<int> const& P,
	int i, int j, string& sol) {
	if (i > j) return;
	if (i == j) sol.push_back(palabra[i]);
	else if (palabra[i] == palabra[j]) {
		sol.push_back(palabra[i]);
		reconstruir(palabra, P, i + 1, j - 1, sol);
		sol.push_back(palabra[j]);
	}
	else if (P[i][j] == P[i + 1][j]) {
		sol.push_back(palabra[i]);
		reconstruir(palabra, P, i + 1, j, sol);
		sol.push_back(palabra[i]);
	}
	else {
		sol.push_back(palabra[j]);
		reconstruir(palabra, P, i, j - 1, sol);
		sol.push_back(palabra[j]);
	}
}
// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	string palabra;
	cin >> palabra;

	if (!std::cin) return false;

	Matriz<int> P(palabra.size(), palabra.size(), -1);

	cout << palabra.size() - palindromo_rec(palabra,0, palabra.size()-1, P)<< " ";

	string sol;
	reconstruir(palabra,P, 0, palabra.size() - 1,sol);
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
