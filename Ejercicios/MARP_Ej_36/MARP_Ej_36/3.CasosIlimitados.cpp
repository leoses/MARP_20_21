#include <iostream>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"
#include <vector>
#include <algorithm>

using namespace std;

void resuelveEscribeSol(int S, int V, vector<int>const& sectores, vector<EntInf> const& dardos) {
	//Calculamos la solucion
	vector<int> sol;
	int i = S, j = V;
	while (j > 0) { // no se ha conseguido toda la puntuacion
		if (sectores[i - 1] <= j && dardos[j] == dardos[j - sectores[i - 1]] + 1) {
			//cogemos sector de tipo i
			sol.push_back(sectores[i - 1]);
			j = j - sectores[i - 1];
		}
		else //cambiamos de sector
			--i;
	}

	//Escribimos solucion
	cout << sol.size() << ": ";
	int k = 0;
	for (; k < sol.size() - 1; k++) {
		cout << sol[k] << " ";
	}
	cout << sol[k] << "\n";

}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int V, S;
	cin >> V >> S;
	if (!std::cin)  // fin de la entrada
		return false;
	vector<int> sectores;
	int sector;

	for (int i = 0; i < S; i++) {
		cin >> sector;
		sectores.push_back(sector);
	}

	vector<EntInf> dardos(V + 1, Infinito);
	dardos[0] = 0;
	for (int i = 1; i <= S; ++i) {
		for (int j = sectores[i - 1]; j <= V; ++j)
			dardos[j] = min(dardos[j], dardos[j - sectores[i - 1]] + 1);
	}

	if (dardos[V] != Infinito) resuelveEscribeSol(S, V, sectores, dardos);
	else cout << "Imposible" << "\n";


	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
 /*  std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());*/
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
   //std::cin.rdbuf(cinbuf);
   //system("PAUSE");
#endif
	return 0;
}
