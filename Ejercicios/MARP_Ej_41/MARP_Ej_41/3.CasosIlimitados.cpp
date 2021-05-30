#include <iostream>
#include <fstream>
#include "Matriz.h"
#include <string>
#include <stack>

using namespace std;

bool resuelveCaso() {

	string p1, p2;
	cin >> p1 >> p2;

	if (!std::cin) return false;

	Matriz<int> tabla(p2.size() + 1, p1.size() + 1, 0);

	for (int i = 1; i < p2.size() + 1; i++) {
		for (int j = 1; j < p1.size() + 1; j++) {
			if (p2[i - 1] == p1[j - 1]) tabla[i][j] = tabla[i - 1][j - 1] + 1;
			else tabla[i][j] = max(tabla[i - 1][j], tabla[i][j - 1]);
		}
	}

	stack<char> sol;

	int i = p2.size();
	int j = p1.size();

	while (i > 0 && j > 0)
	{
		if (p2[i - 1] == p1[j - 1]) {
			sol.push(p2[i - 1]);
			i--;
			j--;
		}
		else if (tabla[i][j] != tabla[i][j - 1]) i--;
		else j--;
	}

	while (!sol.empty()) {
		cout << sol.top();
		sol.pop();
	}

	cout << "\n";

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
