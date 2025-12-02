#ifndef GRAPH_H
#define GRAPH_H

template <typename T>
class Graph {
    private:
        int capacity;
        int count;
        T* vertices;
        int** matrix;
        bool* visited;
        int indexOf(const T& v) const;
        void resetVisited();
        void DFSRecursive(int index);

    public:
        void dijkstra(const T& start);
        void dijkstra(const T& start, const T& end);

        Graph(int c): capacity(c), count(0) {
            vertices = new T[capacity];
            visited = new bool[capacity];
            matrix = new int*[capacity];

            for(int i = 0; i < capacity; i++) {
                matrix[i] = new int[capacity];
                visited[i] = false;
                for (int j = 0; j < capacity; j++) {
                    matrix[i][j] = 0;
                }
            }
        }

        ~Graph() {
            for (int i = 0; i < capacity; i++) {
                delete[] matrix[i];
            }

            delete[] matrix;
            delete[] vertices;
            delete[] visited;
        }

        bool addVertex(const T& val);
        bool addEdge(const T& v, const T& u, int weight = 1, bool directed = false);

        void printMatrix() const;
        void BFS (const T& start);
        void DFS (const T& start);

        void DFSRecursive(const T& start);
};

#include "Graph.tpp"

#endif