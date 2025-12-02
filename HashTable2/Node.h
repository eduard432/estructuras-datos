#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

template <typename T>
class Node {
    private:
        T data;
        Node<T>* prev;
        Node<T>* next;
        int key;
    public:
        Node(const T& val, int k): data(val), prev(nullptr), next(nullptr), key(k) {};

        T getData() const;
        T& getDataRef();

        Node<T>* getPrev() const;
        Node<T>* getNext() const;

        int getKey() const;

        void setKey(int newKey);
        void setData(const T& val);
        void setPrev(Node<T>* node);
        void setNext(Node<T>* node);

        template <typename U>
        friend ostream& operator<<(ostream& os, const Node<U>& s);
};

#include "Node.tpp"

#endif