
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>


using namespace std;

struct registro {
	int momento;
	int id;
	int periodo;
};

bool operator<(registro const& a, registro const& b) {
	return b.momento < a.momento ||
		(a.momento == b.momento && b.id < a.id);
}




// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso(int numElems) {

	// leer los datos de la entrada

	priority_queue<registro> cola;

	for (int i = 0; i < numElems; i++) {
		int id, periodo;
		cin >> id >> periodo;
		cola.push(registro({ periodo, id, periodo }));
	}

	int elemsMos;
	cin >> elemsMos;

	for (int i = 0; i < elemsMos; i++) {
		registro e = cola.top();
		cola.pop();
		e.momento += e.periodo;
		cout << e.id <<"\n";
		cola.push(e);
	}

	cout << "---" << "\n";

}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
 //#ifndef DOMJUDGE
 //   std::ifstream in("casos.txt");
 //   auto cinbuf = std::cin.rdbuf(in.rdbuf());
 //#endif

	int numCasos;
	std::cin >> numCasos;
	while (numCasos != 0) {
		resuelveCaso(numCasos);
		std::cin >> numCasos;
	}

	//   // para dejar todo como estaba al principio
	//#ifndef DOMJUDGE
	//   std::cin.rdbuf(cinbuf);
	//   system("PAUSE");
	//#endif
	return 0;
}
