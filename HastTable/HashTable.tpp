#pragma once
#include "HashTable.h"

template <typename T>
int HashTable<T>::hashFunction(int key) const {
    return key % capacity;
}

template <typename T>
HashTable<T>::HashTable() {
    for(int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}

template <typename T>
HashTable<T>::~HashTable() {
    for(int i = 0; i < capacity; i++) {
        Node<T>* current = table[i];
        while(current) {
            Node<T>* temp = current;
            current = current->getNext();
            delete temp;
        }
    }
}

template <typename T>
void HashTable<T>::insert(int key, const T& value) {
    int index = hashFunction(key);
    Node<T>* current = table[index];
    while(current) {
        if(key = current->getKey()) {
            current->setData();
            return;
        }
    }

    Node<T>* newNode = new Node<T>(value, key);
    newNode->setNext(table[index]);
    table[index] = newNode;
}

template <typename T>
void HashTable<T>::print() const {
    for (int i = 0; i < capacity; i++) {
        Node<T>* current = table[i];
        
        if (current == nullptr) {
            cout << i << ": [Vacio]" << endl;
            continue;
        }

        cout << i << ": [ ";
        while(current) {
            cout << "(" << current->getKey() << "; " << current->getData() << ")";

            if(current->getNext() != nullptr) {
                cout << " -> ";
            }


            current = current->getNext();
        }
        cout << " ]" << endl;
    }
}

template <typename T>
T& HashTable<T>::search(int key) const {
    int index = hashFunction(key);
    Node<T>* current = table[index];

    while(current) {
        if(key == current->getKey()) {
            return current->getDataRef();
        }

        current = current->getNext();
    }
    throw runtime_error("Key no encontrada en la tabla hash");
}

template <typename T>
bool HashTable<T>::remove(int key) {
    int index = hashFunction(key);
    Node<T>* current = table[index];

    if(current == nullptr) {
        cout << "No hay elmentos en este index" << endl;
        return false;
    }

    if(current->getKey() == key) {
        table[index] = current->getNext();
        delete current;
        return true;
    }

    while(current->getNext()) {
        if(key == current->getNext()->getKey()) {
            Node<T>* temp = current->getNext();
            current->setNext(temp->getNext());
            delete temp;
            return true;
        }

        current = current->getNext();
    }

    return false;
}