#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
    private:
        T data;
        Node<T>* next;
    public:
        Node(const T& v): data(v), next(nullptr) {}
        T getData() const;
        T& getDataRef();
        Node<T>* getNext() const;

        void setData(const T& val);
        void setNext(Node<T>* node);

};

#include "Node.tpp"

#endif