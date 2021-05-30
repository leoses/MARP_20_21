// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

struct Persona {
    int tiempo;
    int caja;
};

bool operator> (Persona const& a, Persona const& b) {
    return a.tiempo > b.tiempo || a.tiempo == b.tiempo && a.caja > b.caja;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   int cajas, clientes;
   std::cin >> cajas >> clientes;


   if (cajas == 0 && clientes == 0)
       return false;

   priority_queue<Persona, vector<Persona>, greater<Persona>> cola;

   int tiempo;
   int tiempoTranscurrido = 0;
   int i = 1;
   for (; i <= cajas && i <= clientes; i++) {
       cin >> tiempo;
       cola.push({ tiempo, i });
   }


   if (i <= cajas) cout << i << "\n"; //Por si hay mas cajas que clientes
   else {

       for (int k = 0; k < clientes - cajas; k++) {
           Persona p = cola.top();
           cola.pop();
           cin >> tiempo;
           cola.push({ p.tiempo + tiempo, p.caja });
       }

       cout << cola.top().caja << "\n";

   }
   
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
