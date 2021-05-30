
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>

#include<queue>

struct Par {
	int musicos;
	int partituras;
};

bool partituraMusico(Par const& a) {
	return a.musicos == a.partituras;
}

bool operator<(Par const& a, Par const& b) {
	return (a.musicos / a.partituras) < (b.musicos / b.partituras) ||
		(a.musicos / a.partituras) == (b.musicos / b.partituras) && (a.musicos % a.partituras) < (b.musicos % b.partituras);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int p, q;
	std::cin >> p >> q;

	if (!std::cin)  // fin de la entrada
		return false;

	std::priority_queue<Par> cola;

	//TODOS AL MENOS TIENEN UNA PARTITURA
	int musicos;
	for (int i = 0; i < q; i++) {
		std::cin >> musicos;
		cola.push({ musicos, 1 });
	}

	int partiturasRestantes = p - q;

	Par elem;
	for (int i = 0; (i < (partiturasRestantes)) && !partituraMusico(cola.top()); i++) {
		elem = cola.top();
		cola.pop();
		elem.partituras++;
		cola.push(elem);
	}

	if (cola.top().musicos % cola.top().partituras == 0)
		std::cout << cola.top().musicos / cola.top().partituras << "\n";
	else 
		std::cout << (cola.top().musicos / cola.top().partituras) + 1 << "\n";

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
 /*  std::cin.rdbuf(cinbuf);
   system("PAUSE");*/
#endif
	return 0;
}
