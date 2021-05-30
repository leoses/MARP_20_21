
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>

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
     * Crea un grafo a partir de los datos en el flujo de entrada (si puede).
     * primer es el Ã­ndice del primer vÃ©rtice del grafo en el entrada.
     */
    Grafo(std::istream& flujo, int primer = 0) : _A(0) {
        flujo >> _V;
        if (!flujo) return;
        _ady.resize(_V);
        int E, v, w;
        flujo >> E;
        while (E--) {
            flujo >> v >> w;
            ponArista(v - primer, w - primer);
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

class ResuelveTTL {
public:
    ResuelveTTL(Grafo const& g): visitado(g.V(), false), nVertices(g.V()) {}
    
    void bfs(Grafo const& g, int s, int k) {//s->indice del vértice, k->rango de alcanzado
        std::queue<VerticeNivel> q;
        visitado[s] = true;
        nodosAlcanzados++;
        q.push({ s,0 });
        int i = 0;
        while (!q.empty() && q.front().nivel < k ) {
            VerticeNivel v = q.front(); q.pop();
            for (int w : g.ady(v.vertice)) {
                if (!visitado[w]) {
                    visitado[w] = true;
                    nodosAlcanzados++;
                    q.push({ w, v.nivel + 1 });
                }
            }
        }
    }

    int devuelveInalcanzables() { return nVertices - nodosAlcanzados; }

    void resetData() {
        nodosAlcanzados = 0;
        visitado = std::vector<bool>(nVertices, false);
    }

private:
    std::vector<bool>visitado;
    int nodosAlcanzados = 0;
    int nVertices = 0;

    struct VerticeNivel
    {
        int vertice;
        int nivel;
    };
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   
   int V, C;
   std::cin >> V >> C;

   if (!std::cin)  // fin de la entrada
       return false;
   Grafo g(V);

   int v1, v2;
   for (int i = 0; i < C; i++) {
       std::cin >> v1 >> v2;
       g.ponArista(v1 - 1, v2 - 1);
   }

   ResuelveTTL solucion(g);

   int k, ttl, v;

   std::cin >> k;

   for (int i = 0; i < k; i++) {
       std::cin  >> v >> ttl;
       solucion.bfs(g, v-1, ttl);
       std::cout << solucion.devuelveInalcanzables() << "\n";
       solucion.resetData();
   }

   std::cout << "---\n";
   
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
