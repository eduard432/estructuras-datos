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
}