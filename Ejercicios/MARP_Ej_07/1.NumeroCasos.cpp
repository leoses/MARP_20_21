// Leire Osés Sánchez

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

struct intervalo {
    int ini;
    int f;
    int intervalo;
};

bool operator<(intervalo const& a, intervalo const& b) {
    return a.ini< b.ini;
}

bool operator>(intervalo const& a, intervalo const& b) {
    return b < a;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
    // leer los datos de la entrada
    int tareasUnicas, tareasPeriodicas, tiempo;

    cin >> tareasUnicas >> tareasPeriodicas >> tiempo;
    
    if (!std::cin)return false;

    priority_queue<intervalo, vector<intervalo>, greater<intervalo>> cola;
   
    //Tareas unicas
    for (int i = 0; i < tareasUnicas; i++) { //O(nlog(n) el bucle entero
        int ini, fin;
        cin >> ini >> fin;
        cola.push(intervalo{ ini, fin,0 });
    }

    for (int i = 0; i < tareasPeriodicas; i++) { //O(nlog(n) el bucle entero
        int ini, fin, rep;
        cin >> ini >> fin >> rep;
        cola.push(intervalo({ini, fin, rep}));//log(n) en la altura del arbol
    }

    bool solapamiento = false;
    intervalo i1;
    int ocupado = 0;
    while (!cola.empty() && !solapamiento && cola.top().ini < tiempo ) { //nlog(n)
        i1 = cola.top();
        if (ocupado > i1.ini) solapamiento = true;
        else {
            if (i1.intervalo != 0) cola.push(intervalo{ i1.ini + i1.intervalo, i1.f + i1.intervalo, i1.intervalo });
            ocupado = i1.f;
            cola.pop();//log(n)
        }
    }

    // escribir solución
    if (solapamiento)cout << "SI" << "\n"; //O(1)
    else cout << "NO" << "\n";

    return true;
   
}

int main() {
    while (resuelveCaso());
   return 0;
}
