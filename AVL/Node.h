#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
    private:
        T data;
        Node<T>* left;
        Node<T>* right;
        int height;
    public:
        Node(const T& v): data(v), height(1), right(nullptr), left(nullptr) {}
        T& getData();
        int getHeight() const;
        void setData(const T& v);

        void setRight(Node<T>* right);
        void setLeft(Node<T>* left);
        void setHeight(const int height);

        Node<T>* getLeft() const;
        Node<T>* getRight() const;
};

#include "Node.tpp"

#endif