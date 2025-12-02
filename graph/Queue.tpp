#pragma once
#include "Queue.h"
#include <iostream>

using namespace std;

template <typename T>
void Queue<T>::enqueue(const T& val) {
    Node<T>* newNode = new Node<T>(val);
    if(isEmpty()) {
        frontNode = newNode;
        backNode = newNode;
    } else {
        backNode->setNext(newNode);
        backNode = newNode;
    }

    count++;
}

template <typename T>
T Queue<T>::dequeue () {
    if(isEmpty()) {
        cout << "Empty queue!" << endl;
        throw std::runtime_error("Empty queue")
    } else {
        Node<T>* temp = frontNode;
        frontNode = temp->getNext();
        T returnValue = temp->getData();
        delete temp;
        count--;
        if(count == 0) backNode == nullptr;
        return returnValue;
    }
}

template <typename T>
T Queue<T>::front() {
    if(isEmpty()) {
        cout << "Empty queue" << endl;
        throw std::runtime_error("Empty queue")
    } else {
        return frontNode->getData();
    }
}

template <typename T>
bool Queue<T>::isEmpty() {
    return count == 0;
}

template <typename T>
void Queue<T>::print() const {
    if(isEmpty()) {
        cout << "Lista vacía" << endl;
    } else {
        Node<T>* current = frontNode;
        while(current) {
            cout << " " << current->getData() << "->";
            current = current->getNext();
        }
    }
}