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


class Amigos {
private:
    int maxAmigos_ = 0;
    std::vector<bool> visitados;
public:
    Amigos(Grafo const& g): visitados(g.V(), false) {
        
        for (int i = 0; i < g.V(); i++) {
            if (!visitados[i]) { //Si el vértice todavía no ha sido encontrado en ninguno de los caminos del grafo
                int tam = dfs(g, i); //Calculamos a cuantos elementos se pueden acceder desde ese
                if (tam > maxAmigos_) maxAmigos_ = tam;
            }
        }
    };
    int dfs(Grafo const& g, int v) {
        visitados[v] = true;
        int tam = 1;
        for (int w : g.ady(v)) {
            if (!visitados[w])
                tam += dfs(g, w);
        }

        return tam;
    }

    int maxAmigos() { return maxAmigos_; }

};

// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
   
   // leer los datos de la entrada
    int n, m;

    std::cin >> n >> m;

    //Creamos grafo con n nodos
    Grafo g(n);
    int v1, v2;

    for (int i = 0; i < m; i++) {
        std::cin >> v1 >> v2;
        g.ponArista(v1-1, v2-1); //-1 pq los amigos van numerados de 1  a N y en nuestra representacion de 0 a n-1
    }

    //Resolvemos el problema al llamar a la constructora de amigos
    Amigos amigos(g);

    // escribir solución
    std::cout << amigos.maxAmigos() << "\n";
   
   
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   //std::ifstream in("casos.txt");
   //auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   int numCasos;
   std::cin >> numCasos;
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   //std::cin.rdbuf(cinbuf);
   //system("PAUSE");
#endif
   return 0;
}
