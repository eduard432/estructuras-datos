#ifndef STACK_H
#define STACK_H

#include "Node.h"

template <typename T>
class Stack {
    private:
        unsigned int count;
        Node<T>* topNode;
    public:
        Stack(): count(0), topNode(nullptr) {};
        ~Stack() {
            while(topNode) {
                Node<T>* temp = topNode;
                topNode = topNode->getNext();
                delete temp;
            }
            count = 0;
        }

        void push(const T& val);
        T pop();
        T top();
        bool isEmpty();
        void print() const;
};

#include "Stack.tpp"

#endif