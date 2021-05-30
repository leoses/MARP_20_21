
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Bateria {
    int identificador;
    int tiempoInicial; //ultimo tiempo sumado de recarga de la bateria
    int tiempo; //tiempo global en el que se acaba la duracion actual
};

bool operator< (const Bateria & a, const Bateria & b) {
    return a.tiempo < b.tiempo || a.tiempo == b.tiempo && a.identificador < b.identificador;
}

bool operator> (const Bateria & a, const Bateria & b) {
    return b < a;
}

void escribePilas(priority_queue<Bateria, vector<Bateria>, greater<Bateria>> & pilasSistema) {
    while (!pilasSistema.empty()) {
        Bateria b = pilasSistema.top(); pilasSistema.pop();
        cout << b.identificador << " " << b.tiempo<< "\n";
    }
}


bool resuelveCaso() {
   
   // leer los datos de la entrada
   int b;
   cin >> b;
   if (!std::cin)  // fin de la entrada
      return false;

   priority_queue<Bateria, vector<Bateria>, greater<Bateria>> pilasSistema;
   int dur;
   for (int i = 0; i < b; i++) {
       cin >> dur;
       pilasSistema.push({i+1 , dur, dur});
   }

   queue<Bateria> pilasRepuesto;
   int r;
   cin >> r;
   for (int i = 0; i < r; i++) {
       cin >> dur;
       pilasRepuesto.push({ b + i +1 ,dur, dur });
   }

   int z, t;
   cin >> z >> t;

   int currentTime = 0;
   while (currentTime <= t && !pilasSistema.empty()) {

       //actualizamos tiempo actual hasta que llegue el fin de la vida de la primera pila
       while (currentTime < pilasSistema.top().tiempo && currentTime <= t) { currentTime++; }

       //si se ha acabado el tiempo no seguimos
       if (currentTime > t)continue;

       Bateria primeraEnTerminar = pilasSistema.top(); pilasSistema.pop();

       //Si se ha acabado las recargas de las pilas y todavia quedan de repuesto reponemos
       if (primeraEnTerminar.tiempoInicial - z <= 0 && !pilasRepuesto.empty()) { //Cambiar la bombilla
           primeraEnTerminar = pilasRepuesto.front(); pilasRepuesto.pop();
           primeraEnTerminar.tiempo += currentTime;
           pilasSistema.push(primeraEnTerminar);
       }
       //Si a esta pila todavía le quedan recargas actualizamos valores y la recargamos
       else if (primeraEnTerminar.tiempoInicial - z > 0) {
           primeraEnTerminar.tiempoInicial -= z;
           primeraEnTerminar.tiempo = currentTime + primeraEnTerminar.tiempoInicial;
           pilasSistema.push(primeraEnTerminar);
       }
   }

   if (pilasSistema.empty())cout << "ABANDONEN INMEDIATAMENTE LA BASE\n";
   else {
       if (pilasSistema.size() == b) cout << "CORRECTO\n";
       else  cout << "FALLO EN EL SISTEMA\n";

       escribePilas(pilasSistema);
   }
   cout << "---\n";

   return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

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
