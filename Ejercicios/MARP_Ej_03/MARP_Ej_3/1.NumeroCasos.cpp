
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;
// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int64_t resolver(priority_queue<int64_t, vector<int64_t>, greater<int64_t>>& queue) {

	if (queue.empty() || queue.size() == 1) return 0;
	else {
		int64_t total = 0;
		int64_t elem1, elem2;
		while (queue.size() > 1) {
			elem1 = queue.top();
			queue.pop();
			elem2 = queue.top();
			queue.pop();
			total += elem1 + elem2;
			queue.push(elem1 + elem2);
		}

		return total;
	}


}



// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso(int nSumandos) {

	priority_queue<int64_t, vector<int64_t>, greater<int64_t>> pCola = priority_queue<int64_t, vector<int64_t>, greater<int64_t>>();

	for (int i = 0; i < nSumandos; i++) {
		int n;
		cin >> n;
		pCola.push(n);
	}

	//Resolver problema
	cout << resolver(pCola) << endl;
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
		cin >> numCasos;
	}

	// para dejar todo como estaba al principio
 //#ifndef DOMJUDGE
 //   std::cin.rdbuf(cinbuf);
 //   system("PAUSE");
 //#endif
	return 0;
}
