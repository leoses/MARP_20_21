
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

//
//  bintree_eda.h
//
//  ImplementaciÃ³n de Ã¡rboles binarios (con comparticiÃ³n de nodos)
//  con recorridos en profundidad y por niveles
//  e iterador para recorrer en inorden (basado en una pila de
//  antecesores pendientes)
//
//  Estructuras de Datos
//  Facultad de InformÃ¡tica
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020 Alberto Verdejo
//

#ifndef bintree_eda_h
#define bintree_eda_h

#include <memory>   // shared_ptr, make_shared
#include <stdexcept>
#include <stack>
#include <vector>
#include <queue>
#include <iostream>

template <class T>
class bintree {
protected:
    /*
     Nodo que almacena internamente el elemento (de tipo T),
     y punteros al hijo izquierdo y derecho, que pueden ser
     nullptr si el hijo es vacÃ­o (no existe).
     */
    struct TreeNode;
    using Link = std::shared_ptr<TreeNode>;
    struct TreeNode {
        TreeNode(Link const& l, T const& e, Link const& r) : elem(e), left(l), right(r) {};
        T elem;
        Link left, right;
    };

    // puntero a la raÃ­z del Ã¡rbol
    Link raiz;

    // constructora privada
    bintree(Link const& r) : raiz(r) {}

public:
    // Ã¡rbol vacÃ­o
    bintree() : raiz(nullptr) {}

    // Ã¡rbol hoja
    bintree(T const& e) :
        raiz(std::make_shared<TreeNode>(nullptr, e, nullptr)) {}

    // Ã¡rbol con dos hijos
    bintree(bintree<T> const& l, T const& e, bintree<T> const& r) :
        raiz(std::make_shared<TreeNode>(l.raiz, e, r.raiz)) {}

    // constructora por copia, operador de asignaciÃ³n y destructora por defecto

    // consultar si el Ã¡rbol estÃ¡ vacÃ­o
    bool empty() const {
        return raiz == nullptr;
    }

    // consultar la raÃ­z
    T const& root() const {
        if (empty()) throw std::domain_error("El arbol vacio no tiene raiz.");
        else return raiz->elem;
    }

    // consultar el hijo izquierdo
    bintree<T> left() const {
        if (empty()) throw std::domain_error("El arbol vacio no tiene hijo izquierdo.");
        else return bintree<T>(raiz->left);
    }

    // consultar el hijo derecho
    bintree<T> right() const {
        if (empty()) throw std::domain_error("El arbol vacio no tiene hijo derecho.");
        else return bintree(raiz->right);
    }


    // recorridos

    std::vector<T> preorder() const {
        std::vector<T> pre;
        preorder(raiz, pre);
        return pre;
    }

    std::vector<T> inorder() const {
        std::vector<T> in;
        inorder(raiz, in);
        return in;
    }

    std::vector<T> postorder() const {
        std::vector<T> post;
        postorder(raiz, post);
        return post;
    }

    std::vector<T> levelorder() const {
        std::vector<T> levels;
        if (!empty()) {
            std::queue<Link> pendientes;
            pendientes.push(raiz);
            while (!pendientes.empty()) {
                Link sig = pendientes.front();
                pendientes.pop();
                levels.push_back(sig->elem);
                if (sig->left != nullptr)
                    pendientes.push(sig->left);
                if (sig->right != nullptr)
                    pendientes.push(sig->right);
            }
        }
        return levels;
    }

protected:
    static void preorder(Link a, std::vector<T>& pre) {
        if (a != nullptr) {
            pre.push_back(a->elem);
            preorder(a->left, pre);
            preorder(a->right, pre);
        }
    }

    static void inorder(Link a, std::vector<T>& in) {
        if (a != nullptr) {
            inorder(a->left, in);
            in.push_back(a->elem);
            inorder(a->right, in);
        }
    }

    static void postorder(Link a, std::vector<T>& post) {
        if (a != nullptr) {
            postorder(a->left, post);
            postorder(a->right, post);
            post.push_back(a->elem);
        }
    }

public:
    // iterador que recorre el Ã¡rbol en inorden
    class const_iterator {
    public:
        T const& operator*() const {
            if (ptr == nullptr) throw std::out_of_range("fuera del arbol");
            return ptr->elem;
        }

        T const* operator->() const {
            return &operator*();
        }

        bool operator==(const_iterator const& other) const {
            return ptr == other.ptr;
        }
        bool operator!=(const_iterator const& other) const {
            return !(*this == other);
        }

        const_iterator& operator++() {  // ++ prefijo
            next();
            return *this;
        }

    private:
        friend class bintree;
        Link ptr;
        std::stack<Link> ancestros;

        // constructores privados
        // construye el iterador al primero
        const_iterator(Link raiz) { ptr = first(raiz); }

        // construye el iterador al Ãºltimo
        const_iterator() : ptr(nullptr) {}

        Link first(Link act) {
            if (act == nullptr) {
                return nullptr;
            }
            else {
                while (act->left != nullptr) {
                    ancestros.push(act);
                    act = act->left;
                }
                return act;
            }
        }

        void next() {
            if (ptr == nullptr) {
                throw std::range_error("El iterador no puede avanzar");
            }
            else if (ptr->right != nullptr) { // primero del hijo derecho
                ptr = first(ptr->right);
            }
            else if (ancestros.empty()) { // hemos llegado al final
                ptr = nullptr;
            }
            else { // podemos retroceder
                ptr = ancestros.top();
                ancestros.pop();
            }
        }

    };

    const_iterator begin() const {
        return const_iterator(raiz);
    }
    const_iterator end() const {
        return const_iterator();
    }

};

// lee un Ã¡rbol binario de la entrada estÃ¡ndar
template <typename T>
inline bintree<T> leerArbol(T vacio) {
    T raiz;
    std::cin >> raiz;
    if (raiz == vacio) { // es un Ã¡rbol vacÃ­o
        return {};
    }
    else { // leer recursivamente los hijos
        auto iz = leerArbol(vacio);
        auto dr = leerArbol(vacio);
        return { iz, raiz, dr };
    }
}

#endif // bintree_eda_h

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool esAVL(const bintree<int>& arbol, int & altura, int min, int max) {
    int altDcha, altIzq;
    if (arbol.empty()) {
        altura = 0;
        return true;
    }

    int raiz = arbol.root();

    bool AVLIz = esAVL(arbol.left(),altIzq, min, raiz);
    bool AVLDr = esAVL(arbol.right(),altDcha, raiz, max);
    altura = std::max(altDcha, altIzq)+1;
    bool esBinBusqueda = min < raiz && raiz < max;
    bool esAvl = abs(altIzq - altDcha) <= 1;

    return AVLDr && AVLIz && esBinBusqueda && esAvl ;

}

void resuelveCaso() {
   
   // leer los datos de la entrada
    bintree<int> arbol = leerArbol(-1);
   
    int altura;
   // resolver el caso posiblemente llamando a otras funciones
    if (esAVL(arbol, altura, INT_MIN, INT_MAX)) cout << "SI\n";
    else cout << "NO\n";
   // escribir la solución
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

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
