//
//  Grafo.h
//
//  ImplementaciÃ³n de grafos no dirigidos
//
//  Facultad de InformÃ¡tica
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

#ifndef GRAFO_H_
#define GRAFO_H_

#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>

using Adys = std::vector<int>;  // lista de adyacentes a un vÃ©rtice

class Grafo {
private:
	int _V;  // nÃºmero de vÃ©rtices
	int _A;  // nÃºmero de aristas
	std::vector<Adys> _ady;  // vector de listas de adyacentes
public:

	/**
	 * Crea un grafo con V vÃ©rtices.
	 */
	Grafo(int V) : _V(V), _A(0), _ady(_V) {}

	/**
	 * Crea un grafo a partir de los datos en el flujo de entrada.
	 */
	Grafo(std::istream& flujo) : _A(0) {
		flujo >> _V;
		_ady.resize(_V);
		int E, v, w;
		flujo >> E;
		while (E--) {
			flujo >> v >> w;
			ponArista(v, w);
		}
	}

	/**
	 * Devuelve el nÃºmero de vÃ©rtices del grafo.
	 */
	int V() const { return _V; }

	/**
	 * Devuelve el nÃºmero de aristas del grafo.
	 */
	int A() const { return _A; }

	/**
	 * AÃ±ade la arista v-w al grafo.
	 * @throws domain_error si algÃºn vÃ©rtice no existe
	 */
	void ponArista(int v, int w) {
		if (v < 0 || v >= _V || w < 0 || w >= _V)
			throw std::domain_error("Vertice inexistente");
		++_A;
		_ady[v].push_back(w);
		_ady[w].push_back(v);
	}

	/**
	 * Devuelve la lista de adyacencia de v.
	 * @throws domain_error si v no existe
	 */
	Adys const& ady(int v) const {
		if (v < 0 || v >= _V)
			throw std::domain_error("Vertice inexistente");
		return _ady[v];
	}

	/**
	 * Muestra el grafo en el stream de salida o (para depurar)
	 */
	void print(std::ostream& o = std::cout) const {
		o << _V << " vÃ©rtices, " << _A << " aristas\n";
		for (int v = 0; v < _V; ++v) {
			o << v << ": ";
			for (int w : _ady[v]) {
				o << w << " ";
			}
			o << "\n";
		}
	}
};

/**
 * Para mostrar grafos por la salida estÃ¡ndar
 */
inline std::ostream& operator<<(std::ostream& o, Grafo const& g) {
	g.print(o);
	return o;
}

#endif /* GRAFO_H_ */
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>

class ArbolLibre {
private:
	std::vector<bool> visitados;

public:
	ArbolLibre(Grafo const& g) : visitados(g.V(), false) {
		//si desde el primer todo se pueden llegar a todos y el número de aristas del grafo es estríctamente menor al
		//número de vértices (para que no se formen ciclos ni haya 2 formas distintas de llegar a un nodo desde otro )
		if (dfs(g, 0) == g.V() && g.A() <= g.V()-1 )std::cout << "SI" << "\n";
		else std::cout << "NO" << "\n";
	}

	//Devuelve el numero de elementos visitados desde el nodo v
	//Si se trata de un arbol libre, se deben visitar todos los vértices pero no debe de tener ciclos
	//dfs solo devolverá el número de nodos que se pueden visitar desde el nodo 0
	int dfs(Grafo const& g, int v) {
		visitados[v] = true;
		int tam = 1;
		for (int w : g.ady(v)) {
			if (!visitados[w])
				tam += dfs(g, w);
		}
		return tam;
	}
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	//A = nAristas, v = nVertices
	int A, V;

	std::cin >> V >> A;

	if (!std::cin)  // fin de la entrada
		return false;

	//Creamos el grafo de V vertices
	Grafo g(V);

	//Añadimos las aristas del grafo
	int v1, v2;
	for (int i = 0; i < A; i++) {
		std::cin >> v1 >> v2;
		g.ponArista(v1, v2);
	}

	//Comprobamos si el grafo es un arbol libre
	ArbolLibre a(g);

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
