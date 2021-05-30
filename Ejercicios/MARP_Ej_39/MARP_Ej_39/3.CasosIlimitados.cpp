#include <iostream>
#include <fstream>
#include "Matriz.h"

using namespace std;

struct Cofre {
	int profundidad;
	int oro;
};

int tesoros_rec(vector<Cofre> const& obj, int i, int j,
	Matriz<int>& tesoros) {
	if (tesoros[i][j] != -1) // subproblema ya resuelto
		return tesoros[i][j];
	else if (3 * obj[i - 1].profundidad > j)
		tesoros[i][j] = tesoros_rec(obj, i - 1, j, tesoros);
	else
		tesoros[i][j] = max(tesoros_rec(obj, i - 1, j, tesoros),
			tesoros_rec(obj, i - 1, j - 3 * obj[i - 1].profundidad, tesoros)
			+ obj[i - 1].oro);
	return tesoros[i][j];
}

void tesoro(vector<Cofre> & objetos, int M, vector<bool>& sol) {
	int n = objetos.size();
	Matriz<int> tesoro(n + 1, M + 1, -1);
	for (int i = 0; i < tesoro.numfils(); ++i) tesoro[i][0] = 0;
	for (int j = 1; j < tesoro.numcols(); ++j) tesoro[0][j] = 0;
	int valor = tesoros_rec(objetos, n, M, tesoro);
	// cálculo de los objetos
	int i = n, j = M;
	sol = vector<bool>(n, false);
	int cont = 0;
	while (i > 0 && j > 0) {
		if (tesoro[i][j] != tesoro[i - 1][j]) {
			sol[i - 1] = true; j = j - 3 * objetos[i - 1].profundidad;
			cont++;
		}
		--i;
	}

	cout << tesoro[n][M] << '\n';
	cout << cont << '\n';
	for (int l = 0; l < n; ++l)
		if (sol[l]) cout << objetos[l].profundidad << " " << objetos[l].oro << '\n';
	cout << "---" << '\n';
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int T, N;
	cin >> T>>N;

	if (!std::cin) return false;

	vector<Cofre> cofres;
	int profundidad, oro;
	for (int i = 0; i < N; i++) {
		cin >> profundidad >> oro;
		cofres.push_back({ profundidad, oro});
	}
	
	vector<bool> sol;
	tesoro(cofres, T, sol);

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
