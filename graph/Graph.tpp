#pragma once
#include "Graph.h"
#include "Queue.h"
#include "Stack.h"

#include <iostream>

using namespace std;

template <typename T>
int Graph<T>::indexOf(const T& val) const {
    for(int i = 0; i < count; i++) {
        if(vertices[i] == val) {
            return i;
        }
    }

    return -1;
}

template <typename T>
bool Graph<T>::addVertex (const T& val) {
    // Capacidad máxima
    if(count >= capacity) {
        return false;
    }

    // Ya existe
    if(indexOf(val) != -1) {
        return false;
    }

    vertices[count] = val;
    count++;

    return true;
}

template<typename T>
void Graph<T>::printMatrix() const {
    cout << "------- MATRIX -------" << endl;

    cout << "    \t\t";
    for (int i = 0; i < count; i++) {
        cout << vertices[i] << "\t";
    }
    cout << endl;

    for (int i = 0; i < count; i++) {
        cout << vertices[i] << "\t\t";
        for (int j = 0; j < count; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

template <typename T>
bool Graph<T>::addEdge(const T& v, const T& u, int weight, bool directed) {
    int vIndex = indexOf(v);
    int uIndex = indexOf(u);

    if(vIndex == -1 || uIndex == -1) {
        return false;
    }

    matrix[vIndex][uIndex] = weight;

    if(!directed) {
        matrix[uIndex][vIndex] = weight;
    }

    return true;
}

template <typename T>
void Graph<T>::resetVisited() {
    for(int i = 0; i < capacity; i++) {
        visited[i] = false;
    }
}

template <typename T>
void Graph<T>::BFS(const T& start) {
    int startIndex = indexOf(start);
    if(startIndex == -1) {
        return;
    }
    resetVisited(); 
    visited[startIndex] = true;
    Queue<int> queue;
    queue.enqueue(startIndex);

    while(!queue.isEmpty()) {
        int index = queue.dequeue();
        // Procesamiento del nodo:
        cout << vertices[index] << "->";
        for(int neighIndex = 0; neighIndex < count; neighIndex++) {
            if(matrix[index][neighIndex] != 0 && !visited[neighIndex]) {
                visited[neighIndex] = true;
                queue.enqueue(neighIndex);
            }
        }
    }

    cout << endl;
}

template <typename T>
void Graph<T>::DFS(const T& start) {
    int startIndex = indexOf(start);
    if(startIndex == -1) {
        return;
    }

    resetVisited();
    
    visited[startIndex] = true;
    Stack<int> stack;
    stack.push(startIndex);

    while(!stack.isEmpty()) {
        int index = stack.pop();
        // Procesamiento del nodo
        cout << vertices[index] << "->";
        for(int neighIndex = 0; neighIndex  < count; neighIndex++) {
            if(matrix[index][neighIndex] != 0 && !visited[neighIndex]) {
                visited[neighIndex] = true;
                stack.push(neighIndex);
            }
        }
    }
    cout << endl;
}

template <typename T>
void Graph<T>::DFSRecursive(const T& start) {
    int startIndex = indexOf(start);
    if(startIndex == -1) {
        return;
    }

    resetVisited();
    DFSRecursive(startIndex);
    cout << endl;
}

template <typename T>
void Graph<T>::DFSRecursive(int index) {
    visited[index] = true;
    // Procesamiento del nodo:
    cout << vertices[index] << "->";

    for(int neighIndex = 0; neighIndex < count; neighIndex++) {
        if(matrix[index][neighIndex] != 0 && !visited[neighIndex]) {
            DFSRecursive(neighIndex);
        }
    }
}


template <typename T>
void Graph<T>::dijkstra(const T& start) {
    int startIndex = indexOf(start);
    if(startIndex == -1) {
        return;
    }

    int* distances = new int[count];
    // No confundir con visited de BSF/DSF
    bool* used = new bool[count];

    // Inicializamos las distancias como "inifinito" y visitado/usado:
    // como no visitado:
    for(int i = 0; i < count; i++) {
        distances[i] = INT_MAX;
        used[i] = false;
    }

    // La distancia de start a si mismo es cero
    // Permite iniciar el ciclo del algoritmo 
    distances[startIndex] = 0;

    for(int i = 0; i < count; i++) {
        // Indiice del nodo más pequeño a encontar
        int u = -1;
        // Dicha distancia a "superar" (la más pequeña)
        int minDist = INT_MAX;
        for (int j = 0; j < count; j++) {
            if(!used[j] && distances[j] < minDist) {
                minDist = distances[j];
                u = j;
            }
        }

        // No hay más vertics más pequeños o a alcanzar
        if(u == -1) {
            break;
        }

        // Marcamos como visitado/usado/procesado el nodo
        used[u] = true;

        // Recorremos toda la fila de ndodos de ese nodo más pequeño
        for (int k = 0; k < count; k++) {
            // Obtenemos el peso que hay con cada nodo
            int weight = matrix[u][k];

            // Condición para chechar si existe una arista
            if(weight > 0) {
                // Primero checo que el nodo vecino no haya sido procesado previamente
                // Segundo, medidia de seguridad para verificar que no sea INT_MAX
                // Tercer, verifico que si:
                // "Si llegar a k pasando por u es más barato que la distancia que ya tengo para k, entonces actualizo."
                if(!used[k] && distances[u] != INT_MAX && distances[u] + weight < distances[k]) {
                    // Actualizar/relajar la distancia
                    distances[k] = distances[u] + weight;
                }
            }
        }
    }

    for (int i = 0; i < count; i++) {
        cout << distances[i] << ", ";
    }

    delete[] distances;
    delete[] used;
}

template <typename T>
void Graph<T>::dijkstra(const T& start, const T& end) {
    int startIndex = indexOf(start);
    int endIndex = indexOf(end);

    if(startIndex == -1 || endIndex == -1) {
        return;
    }

    int* distances = new int[count];
    bool* used = new bool[count];
    int* prevs = new int[count];

    for (int i = 0; i < count; i++) {
        distances[i] = INT_MAX;
        used[i] = false;
        prevs[i] = -1;
    }

    distances[startIndex] = 0;

    for(int i = 0; i < count; i++) {
        int u = -1;
        int minDist = INT_MAX;
        for(int j = 0; j < count; j++) {
            if(!used[j] && distances[j] < minDist) {
                minDist = distances[j];
                u = j;
            }
        }

        if(u == -1) {
            // No hay más vértices alcanzables
            break;
        }

        if(u == endIndex) {
            // Llegamos al nodo destino
            break;
        }

        used[u] = true;

        // Recorremos toda la fila de ndodos de ese nodo más pequeño
        for (int k = 0; k < count; k++) {
            // Obtenemos el peso que hay con cada nodo
            int weight = matrix[u][k];

            // Condición para chechar si existe una arista
            if(weight > 0) {
                // Primero checo que el nodo vecino no haya sido procesado previamente
                // Segundo, medidia de seguridad para verificar que no sea INT_MAX
                // Tercer, verifico que si:
                // "Si llegar a k pasando por u es más barato que la distancia que ya tengo para k, entonces actualizo."
                if(!used[k] && distances[u] != INT_MAX && distances[u] + weight < distances[k]) {
                    // Actualizar/relajar la distancia
                    distances[k] = distances[u] + weight;
                    prevs[k] = u;
                }
            }
        }
    }

    if(distances[endIndex] == INT_MAX) {
        cout << "No existe un camino hacia el nodo final" << endl; 
        delete[] distances;
        delete[] used;
        delete[] prevs;
        return;
    }

    // Reconstrucción del camino
    // pathSize sirve como inidice del array resultante
    int pathSize = 0;
    // path array resultante con los prevs en orden;
    int* path = new int[count];
    // current sirve como indice del arragleo prevs
    // inidice no lineal, va saltando hacia donde se diriga el siguiente indice
    int current = endIndex;

    // Verificamos que current no haya lelgado al inicio o a un nodo donde no haya pev;
    // Verificamos que el camino no sea más largo que la cantidad de nodos guardados en el grafo
    while(current != -1 && pathSize < count) {
        path[pathSize] = current;
        pathSize++;
        if(current == startIndex) {
            // Llegamos al inicio
            break;
        }
        // Nos movemos al inidice que indique el array de prevs;
        current = prevs[current];
    }

    // Gráficamos el camino, está el reves, empezamos por nodo end
    // pero queremos mostrar la ruta de start a end

    cout << "El mejor camino de " << start << " a " << end << ":" << endl;
    for(int i = pathSize - 1; i >= 0; i--) {
        cout << vertices[path[i]];
        if(i > 0) {
            cout << " -> ";
        }
    }
    cout << " (distancia = " << distances[endIndex] << ")" << endl;

    delete[] distances;
    delete[] used;
    delete[] prevs;
    delete[] path;
}