
// Nombre y Apellidos



#include <iostream>
#include <fstream>
#include "ConjuntosDisjuntos.h"
//#include "GrafosValorados.h"
#include "PriorityQueue.h"
#include <queue>



#ifndef GRAFOVALORADO_H_
#define GRAFOVALORADO_H_

//
//  GrafoValorado.h
//
//  ImplementaciÃ³n de grafos no dirigidos valorados
//
//  Facultad de InformÃ¡tica
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>


template <typename Valor>
class Arista {
public:
	Arista() : pimpl(nullptr) {}
	Arista(int v, int w, Valor valor) : pimpl(std::make_shared<Arista_impl>(v, w, valor)) {}

	int uno() const { return pimpl->v; }
	int otro(int u) const { return (u == pimpl->v) ? pimpl->w : pimpl->v; }
	Valor valor() const { return pimpl->valor; }

	void print(std::ostream& o = std::cout) const {
		o << "(" << pimpl->v << ", " << pimpl->w << ", " << pimpl->valor << ")";
	}

	bool operator<(Arista<Valor> const& b) const {
		return valor() < b.valor();
	}
	bool operator>(Arista<Valor> const& b) const {
		return b.valor() < valor();
	}
private:
	struct Arista_impl {
		int v, w;
		Valor valor;
		Arista_impl(int v, int w, Valor valor) : v(v), w(w), valor(valor) {}
	};

	std::shared_ptr<Arista_impl> pimpl; // puntero a la arista "de verdad"
};

template <typename Valor>
inline std::ostream& operator<<(std::ostream& o, Arista<Valor> const& ar) {
	ar.print(o);
	return o;
}


template <typename Valor>
using AdysVal = std::vector<Arista<Valor>>;  // lista de adyacentes a un vÃ©rtice

template <typename Valor>
class GrafoValorado {
public:

	/**
	 * Crea un grafo valorado con V vÃ©rtices, sin aristas.
	 */
	GrafoValorado(int V) : _V(V), _A(0), _ady(_V), visit(V, false) { }

	/**
	 * Crea un grafo valorado a partir de los datos en el flujo de entrada (si puede).
	 * primer es el Ã­ndice del primer vÃ©rtice del grafo en el entrada.
	 */
	GrafoValorado(std::istream& flujo, int primer = 0) : _A(0) {
		flujo >> _V;
		if (!flujo) return;
		_ady.resize(_V);
		int E, v, w;
		Valor c;
		flujo >> E;
		while (E--) {
			flujo >> v >> w >> c;
			ponArista({ v - primer, w - primer, c });
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
	 * AÃ±ade una arista al grafo.
	 * @throws invalid_argument si algÃºn vÃ©rtice no existe
	 */
	void ponArista(Arista<Valor> arista) {
		int v = arista.uno(), w = arista.otro(v);
		if (v < 0 || v >= _V || w < 0 || w >= _V)
			throw std::invalid_argument("Vertice inexistente");
		++_A;
		_ady[v].push_back(arista);
		_ady[w].push_back(arista);
	}

	/**
	 * Devuelve la lista de adyacentes de v.
	 * @throws invalid_argument si v no existe
	 */
	AdysVal<Valor> const& ady(int v) const {
		if (v < 0 || v >= _V)
			throw std::invalid_argument("Vertice inexistente");
		return _ady[v];
	}

	/**
	 * Devuelve las aristas del grafo.
	 */
	std::vector<Arista<Valor>> aristas() const {
		std::vector<Arista<Valor>> ars;
		for (int v = 0; v < V(); ++v)
			for (auto arista : ady(v))
				if (v < arista.otro(v))
					ars.push_back(arista);
		return ars;
	}

	/**
	 * Muestra el grafo en el stream de salida o
	 */
	void print(std::ostream& o = std::cout) const {
		o << _V << " vÃ©rtices, " << _A << " aristas\n";
		for (auto v = 0; v < _V; ++v) {
			o << v << ": ";
			for (auto const& w : _ady[v]) {
				o << w << " ";
			}
			o << "\n";
		}
	}

	// visita los nodos alcanzables desde v respetando el umbral
	void dfs(int v) {
		visit[v] = true;
		verticesVisitados++;
		for (auto a : ady(v)) {
			int w = a.otro(v);
			if (!visit[w])
				dfs(w);
		}
	}

	bool esConexo() { return verticesVisitados == _V; }

private:
	int _V;   // nÃºmero de vÃ©rtices
	int _A;   // nÃºmero de aristas
	std::vector<AdysVal<Valor>> _ady;   // vector de listas de adyacentes
	std::vector<bool> visit;
	int verticesVisitados = 0;
};


/**
 * Para mostrar grafos por la salida estÃ¡ndar.
 */

template <typename Valor>
inline std::ostream& operator<<(std::ostream& o, GrafoValorado<Valor> const& g) {
	g.print(o);
	return o;
}

#endif /* GRAFOVALORADO_H_ */



template <typename Valor>
class ARM_Kruskal {
private:
	std::vector<Arista<Valor>> _ARM;
	Valor coste;
public:
	Valor costeARM() const {
		return coste;
	}
	std::vector<Arista<Valor>> const& ARM() const {
		return _ARM;
	}
	ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0) {
		PriorityQueue<Arista<Valor>> pq(g.aristas());
		ConjuntosDisjuntos cjtos(g.V());
		while (!pq.empty()) {
			auto a = pq.top(); pq.pop();
			int v = a.uno(), w = a.otro(v);
			if (!cjtos.unidos(v, w)) {
				cjtos.unir(v, w);
				_ARM.push_back(a); coste += a.valor();
				if (_ARM.size() == g.V() - 1) break;
			}
		}
	}
};



// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int islas, puentes;
	std::cin >> islas >> puentes;

	if (!std::cin)return false;
	GrafoValorado<int> g(islas);

	int v1, v2, valor;

	for(int i = 0; i < puentes; i++) {
		std::cin >> v1 >> v2 >> valor;
		g.ponArista({ v1-1, v2-1, valor });
	}
	g.dfs(0);

	// escribir sol
	if (g.esConexo()) {
		ARM_Kruskal<int> recMinimo(g);
		std::cout << recMinimo.costeARM() << "\n";
	}
	else std::cout << "No hay puentes suficientes\n";


	
	

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
