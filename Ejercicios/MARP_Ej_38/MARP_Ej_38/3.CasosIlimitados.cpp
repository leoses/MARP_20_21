#include <iostream>
#include <fstream>
#include <vector>

constexpr int Infinito = 1000000000;

struct Bombilla {
	int potencia;
	int precio;
	Bombilla():Bombilla(0,0){}
	Bombilla(int pot, int pre = 0) { potencia = pot; precio = pre; }
};

using namespace std;

Bombilla devolverPrecio(vector<Bombilla> const& M,int Pmin, int Pmax) {
	int n = M.size();
	vector<int> precio(Pmax + 1, Infinito);
	precio[0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = M[i-1].potencia; j <= Pmax; ++j)
			precio[j] = min(precio[j], precio[j - M[i - 1].potencia] + M[i-1].precio);
	}

	Bombilla sol;
	sol.precio = precio[Pmin];
	sol.potencia = Pmin;

	for (int i = Pmin + 1; i <= Pmax; i++) {
		if (sol.precio > precio[i]) {
			sol.precio = precio[i];
			sol.potencia = i;
		}
	}

	return sol;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	int n, pMax, pMin;
	cin >> n >> pMax >> pMin;

	if (!std::cin) return false;

	vector<Bombilla> bombillas;
	int aux;
	for (int i = 0; i < n; i++) {
		cin >> aux;
		bombillas.push_back(Bombilla(aux));
	}

	for (int i = 0; i < n; i++) {
		cin >> aux;
		bombillas[i].precio = aux;
	}

	Bombilla sol = devolverPrecio(bombillas, pMin, pMax);

	if (sol.precio == Infinito) cout << "IMPOSIBLE\n";
	else cout << sol.precio << " " << sol.potencia << "\n";

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
