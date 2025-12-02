#pragma once
#include "Stack.h"
#include <iostream>

using namespace std;

template <typename T>
void Stack<T>::push(const T& val) {
    Node<T>* newNode = new Node<T>(val);
    newNode->setNext(topNode);
    topNode = newNode;

    count++;
}

template <typename T>
T Stack<T>::pop () {
    if(isEmpty()) {
        cout << "Empty queue!" << endl;
        throw std::runtime_error("Empty stack");
    } else {
        Node<T>* temp = topNode;
        topNode = temp->getNext();
        T returnValue = temp->getData();
        delete temp;
        count--;
        return returnValue;
    }
}

template <typename T>
T Stack<T>::top() {
    if(isEmpty()) {
        cout << "Empty queue" << endl;
        throw std::runtime_error("Empty stack");
    } else {
        return topNode->getData();
    }
}

template <typename T>
bool Stack<T>::isEmpty() {
    return count == 0;
}

template <typename T>
void Stack<T>::print() const {
    if(isEmpty()) {
        cout << "Lista vacía" << endl;
    } else {
        Node<T>* current = topNode;
        while(current) {
            cout << " " << current->getData() << "->";
            current = current->getNext();
        }
    }
}