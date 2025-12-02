#include <iostream>
using namespace std;

// ==========================================
// NODO AVL
// ==========================================

class NodoAVL {
public:
    int dato;
    int altura;
    NodoAVL* izquierdo;
    NodoAVL* derecho;

    NodoAVL(int d) {
        dato = d;
        altura = 1;
        izquierdo = nullptr;
        derecho = nullptr;
    }
};

// ==========================================
// ÁRBOL AVL
// ==========================================

class ArbolAVL {
private:
    NodoAVL* raiz;

    // contadores de rotaciones
    int rotacionesIzquierdaSimples;
    int rotacionesDerechaSimples;
    int rotacionesDobles;

    int altura(NodoAVL* nodo) {
        if (nodo == nullptr) return 0;
        return nodo->altura;
    }

    int maxEntero(int a, int b) {
        return (a > b) ? a : b;
    }

    int obtenerBalance(NodoAVL* nodo) {
        if (nodo == nullptr) return 0;
        return altura(nodo->izquierdo) - altura(nodo->derecho);
    }

    // Rotación simple a la derecha
    NodoAVL* rotacionDerecha(NodoAVL* y) {
        NodoAVL* x = y->izquierdo;
        NodoAVL* T2 = x->derecho;

        // Rotar
        x->derecho = y;
        y->izquierdo = T2;

        // Actualizar alturas
        y->altura = 1 + maxEntero(altura(y->izquierdo), altura(y->derecho));
        x->altura = 1 + maxEntero(altura(x->izquierdo), altura(x->derecho));

        rotacionesDerechaSimples++;

        // Nueva raíz del subárbol
        return x;
    }

    // Rotación simple a la izquierda
    NodoAVL* rotacionIzquierda(NodoAVL* x) {
        NodoAVL* y = x->derecho;
        NodoAVL* T2 = y->izquierdo;

        // Rotar
        y->izquierdo = x;
        x->derecho = T2;

        // Actualizar alturas
        x->altura = 1 + maxEntero(altura(x->izquierdo), altura(x->derecho));
        y->altura = 1 + maxEntero(altura(y->izquierdo), altura(y->derecho));

        rotacionesIzquierdaSimples++;


        // Nueva raíz del subárbol
        return y;
    }

    NodoAVL* insertarRec(NodoAVL* nodo, int valor) {
        // 1) Inserción tipo BST normal
        if (nodo == nullptr) {
            NodoAVL* nuevo = new NodoAVL(valor);
            return nuevo;
        }

        if (valor < nodo->dato) {
            nodo->izquierdo = insertarRec(nodo->izquierdo, valor);
        } else if (valor > nodo->dato) {
            nodo->derecho = insertarRec(nodo->derecho, valor);
        } else {
            // valor duplicado, no se inserta
            return nodo;
        }

        // 2) Actualizar altura
        nodo->altura = 1 + maxEntero(altura(nodo->izquierdo), altura(nodo->derecho));

        // 3) Calcular factor de balance
        int balance = obtenerBalance(nodo);

        // Si está desbalanceado, imprimir mensaje
        if (balance > 1 || balance < -1) {
            cout << "Desbalance en nodo " << nodo->dato 
                 << " (balance = " << balance << ")\n";
        }
        
        if(balance > 1 && valor < nodo->izquierdo->dato) {
            return rotacionDerecha(nodo);
        }

        if(balance > 1 && valor > nodo->izquierdo->dato) {
            nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
            rotacionesDobles++;
            return rotacionDerecha(nodo);
        }

        if(balance < - 1 && valor < nodo->derecho->dato) {
            nodo->derecho = rotacionDerecha(nodo->derecho);
            rotacionesDobles++;
            
            return rotacionIzquierda(nodo);
        }

        if(balance < - 1 && valor > nodo->derecho->dato) {
            return rotacionIzquierda(nodo);
        }

        // 4) Casos de rotación
        // Aquí es donde el alumno debe IDENTIFICAR el caso (LL, RR, LR, RL)
        // y llamar a la rotación correspondiente.

        // TODO: Caso LL (Izquierda - Izquierda)
        // if ( ... condición de LL ... ) {
        //     return rotacionDerecha(nodo);
        // }

        // TODO: Caso RR (Derecha - Derecha)
        // if ( ... condición de RR ... ) {
        //     return rotacionIzquierda(nodo);
        // }

        // TODO: Caso LR (Izquierda - Derecha) -> rotación doble
        // if ( ... condición de LR ... ) {
        //     nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        //     rotacionesDobles++;
        //     return rotacionDerecha(nodo);
        // }

        // TODO: Caso RL (Derecha - Izquierda) -> rotación doble
        // if ( ... condición de RL ... ) {
        //     nodo->derecho = rotacionDerecha(nodo->derecho);
        //     rotacionesDobles++;
        //     return rotacionIzquierda(nodo);
        // }
        


        // Si no hubo desbalance que requiera rotación, regresa el nodo tal cual
        return nodo;
    }

public:
    ArbolAVL() {
        raiz = nullptr;
        rotacionesIzquierdaSimples = 0;
        rotacionesDerechaSimples = 0;
        rotacionesDobles = 0;
    }

    void insertar(int valor) {
        raiz = insertarRec(raiz, valor);
    }

    void imprimirResumenRotaciones() {
        cout << "Rotaciones simples izquierda: " << rotacionesIzquierdaSimples << "\n";
        cout << "Rotaciones simples derecha: " << rotacionesDerechaSimples << "\n";
        cout << "Rotaciones dobles: " << rotacionesDobles << "\n";
    }
};

// ==========================================
// MAIN
// ==========================================

int main() {
    ArbolAVL arbol;

    // Secuencia que provoca rotaciones simples y dobles
    int valores[] = {30, 10, 20, 5, 3, 4, 40, 50, 45};
    int n = 9;

    cout << "Insertando valores en el AVL:\n";
    for (int i = 0; i < n; i++) {
        cout << "Insertar: " << valores[i] << endl;
        arbol.insertar(valores[i]);
    }

    cout << "\nResumen de rotaciones:\n";
    arbol.imprimirResumenRotaciones();

    return 0;
}