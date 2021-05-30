
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "Digrafo.h"
#include <queue>

class SerpientesEscaleras {
private:
    std::vector<bool> visitados;
    std::vector<int> distancia;

    void bfs(Digrafo const& g, int k) {
        std::queue<int> q;
        int s = 0;
        distancia[s] = 0; visitados[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            
            if (v == g.V() - 1)break; //Si ya hemos llegado al ultimo, terminamos
            
            for (int x = 1; x <= k; x++) {
                if (v+x < g.V() && !visitados[v+x]) {
                    //Numeros alcanzables por el dado
                    if (g.ady(v + x).empty()) { //Solo te puedes quedar en una casilla si no tiene serpientes o escaleras
                        distancia[v + x] = distancia[v] + 1; visitados[v + x] = true;
                        q.push(v + x);
                    }

                    for (int w : g.ady(v + x)) { 
                        //Serpientes y escaleras
                        if (!visitados[w]) {
                            distancia[w] = distancia[v] + 1; visitados[w] = true;
                            q.push(w);
                        }
                    }
                }
            }

        }
    }

public:
    SerpientesEscaleras(Digrafo const& g, int k) : visitados(g.V(), false), distancia(g.V(), -1) {
        bfs(g, k);

        std::cout << distancia[g.V() - 1] << "\n";
    }


};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   

    int n, k, s, e;
    std::cin >> n >> k >> s >> e;
   
   if (n == 0 && k == 0 && s == 0 && e == 0)
      return false;

   Digrafo g(n * n);

   int v1, v2;

   //Serpientes y escaleras
   for (int i = 0; i < (s+e); i++) {
       std::cin >> v1 >> v2;
       g.ponArista(v1 - 1, v2 - 1);
   }

   SerpientesEscaleras solucion(g, k);
   
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
