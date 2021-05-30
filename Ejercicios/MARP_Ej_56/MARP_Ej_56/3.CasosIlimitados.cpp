
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

enum tipo{nueve, uno};
struct bombilla {
	tipo type;
	int duracion;
};

bool operator<(const bombilla& a, const bombilla& b) {
	return a.duracion < b.duracion;
}

void resuelve(priority_queue<bombilla> bombillas9, priority_queue<bombilla> bombillas1, int n) {

	while (!bombillas1.empty() && !bombillas9.empty()) {//HASTA GASTAR TODAS
		int horasVuelo = 0, i = 0;
		vector<bombilla> sinAcabar;
		while (i < n && !bombillas1.empty() && !bombillas9.empty()) { //UN DIA SOLO
			bombilla bombilla9 = bombillas9.top(); bombillas9.pop();
			bombilla bombilla1 = bombillas1.top(); bombillas1.pop();

			//Si no entra en ninguno de estos ifs es que el tiempo de las 
			//bombillas es el mismo
			int menor = bombilla9.duracion; 

			if (bombilla9.duracion > bombilla1.duracion) {
				menor = bombilla1.duracion;
				bombilla9.duracion -= menor;
				sinAcabar.push_back(bombilla9);
			}
			else if (bombilla9.duracion < bombilla1.duracion){
				bombilla1.duracion -= menor;
				sinAcabar.push_back(bombilla1);
			}
			horasVuelo += menor;
			i++;
		}

		//Ya hemos usado todos los drones y es ahora cuando recogemos las pilas 
		//que no se han gastado del todo
		for (bombilla b : sinAcabar) {
			if (b.type == tipo::nueve) bombillas9.push(b);
			else bombillas1.push(b);
		}

		if(!bombillas1.empty() && !bombillas9.empty()) cout << horasVuelo << " ";
		else cout << horasVuelo;
	}
	cout << "\n";
}
 
bool resuelveCaso() {

	// leer los datos de la entrada
	int n, a, b;
	cin >> n >> a >> b;
	if (!std::cin)  // fin de la entrada
		return false;

	priority_queue<bombilla> bombillas9;
	priority_queue<bombilla> bombillas1;

	int duracion;
	for (int i = 0; i < a; i++) {
		cin >> duracion;
		bombillas9.push({ tipo::nueve,duracion });
	}
	for (int i = 0; i < b; i++) {
		cin >> duracion;
		bombillas1.push({ tipo::uno,duracion });
	}
	
	resuelve(bombillas9, bombillas1, n);

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
