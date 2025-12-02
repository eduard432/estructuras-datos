#include "Graph.h"
#include <string>

using namespace std;

int main () {
    Graph<string > grafo(10);

    grafo.addVertex("A");
    grafo.addVertex("B");
    grafo.addVertex("C");
    grafo.addVertex("D");
    grafo.addVertex("E");
    grafo.addEdge("A", "B", 1);
    grafo.addEdge("A", "C", 4);
    grafo.addEdge("B", "C", 2);
    grafo.addEdge("B", "D", 5);
    grafo.addEdge("C", "D", 1);
    grafo.addEdge("D", "E", 1);

    grafo.printMatrix();
    grafo.dijkstra("A", "E");
    

    return 0;
}