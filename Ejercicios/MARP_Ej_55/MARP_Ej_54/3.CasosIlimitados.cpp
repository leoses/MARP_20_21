
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

struct Conciertos {
	int grupos;
	int precio;
};

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {

	// leer los datos de la entrada
	int presupuesto, conciertos;
	cin >> presupuesto >> conciertos;
	if (!std::cin)  // fin de la entrada
		return false;

	vector<Conciertos> conciertosInfo;
	int grup, coste;
	for (int i = 0; i < conciertos; i++) {
		cin >> grup >> coste;
		conciertosInfo.push_back({ grup, coste });
	}

	//Resolver
	vector<int> C(presupuesto + 1, 0);
	for (int i = 1; i <= conciertos; i++) {
		for (int j = presupuesto; j >= 0; j--) {
			if (j >= conciertosInfo[i - 1].precio) 
				C[j] = max(C[j], C[j - conciertosInfo[i - 1].precio] + conciertosInfo[i - 1].grupos);
		}
	}

	//Escribir solucion
	cout << C[presupuesto] << "\n";

#pragma region Solucion_con_Matriz

	//Matriz<int> C(conciertos + 1, presupuesto + 1, 0);

	//// resolver el caso posiblemente llamando a otras funciones
	//for (int i = 1; i <= conciertos; i++) {
	//	for (int j = presupuesto; j >= 0; j--) {
	//		if (j < conciertosInfo[i - 1].precio) C[i][j] = C[i - 1][j];
	//		else {
	//			C[i][j] = max(C[i - 1][j], C[i - 1][j - conciertosInfo[i - 1].precio] + conciertosInfo[i - 1].grupos);
	//		}
	//	}
	//}

	//// escribir la solución
	//cout << C[conciertos][presupuesto] << "\n";
#pragma endregion

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

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
