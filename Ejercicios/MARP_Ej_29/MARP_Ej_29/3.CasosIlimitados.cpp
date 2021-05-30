
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

struct Pelicula {
	int inicio;
	int fin;
};

bool operator<(Pelicula const& a, Pelicula const& b) {
	return a.fin < b.fin;
}

bool operator>(Pelicula const& a, Pelicula const& b) {
	return b < a;
}

int PeliculasMax(priority_queue< Pelicula, vector<Pelicula>, greater<Pelicula>>& peliculas) {
	int nPelis = 1;
	int finT = peliculas.top().fin;
	peliculas.pop();
	while (!peliculas.empty()) {
		Pelicula peli = peliculas.top();
		peliculas.pop();
		if (peli.inicio >= finT + 10) {
			nPelis++;
			finT = peli.fin;
		}
	}

	return nPelis;
}

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {

	// leer los datos de la entrada
	int N;
	cin >> N;

	if (N == 0)
		return false;
	char c;
	int h, min, dur;
	int inicio, fin;
	//vector<Pelicula> peliculas;
	priority_queue < Pelicula, vector<Pelicula>, greater<Pelicula>> peliculas;
	for (int i = 0; i < N; i++) {
		cin >> h;
		cin >> c;
		cin >> min;

		cin >> dur;
		inicio = (h * 60) + min;
		fin = inicio + dur;

		peliculas.push({ inicio, fin });
	}

	//sort(peliculas.begin(), peliculas.end());

	// escribir sol
	int pelisMax = PeliculasMax(peliculas);
	cout << pelisMax << '\n';

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
