#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Node.h"

template <typename T>
class HashTable {
    private:
        const int capacity = 20;
        Node<T>* table[capacity];
        int hashFunction (int key) {
            return key % capacity;
        };
    public:
        HashTable() {
            for(int i = 0; i < capacity; i++) {
                table[i] = nullptr;
            }
        }
        ~HashTable() {
            for(int i = 0; i < capacity; i++) {
                Node<T>* current = table[i];
                while(current) {
                    Node<T>* temp = current;
                    current = temp ->getNext();
                    delete temp;
                }
            }
        }
        void insert(int key, const T& val) {
            int index = hashFunction(key);

            Node<T>* current = table[index];
            while(current) {
                if(current->getKey() == key) {
                    current->setData(val);
                    return;
                }
                current = current->getNext();
            }
            Node<T>* newNode = new Node(val, key);
            newNode->setNext(table[index]);
            table[index] = newNode;
        }

        bool remove(int key) {
            int index = hashFunction(key);

            Node<T>* current = table[index];

            if(current == nullptr) {
                return false;
            }

            if(current->getKey() == key) {
                table[index] = current->getNext();
                delete current;
                return true;
            }

            while(current->getNext()) {
                if(current->getNext()->getKey() == key) {
                    Node<T>* temp = current->getNext();
                    current->setNext(temp->getNext());
                    delete temp;
                    return true;
                }
                current = current->getNext();
            }

            return false;
        }
        T& search(int key) const {
            int index = hashFunction(key);
            Node<T>* current = table[index];
            while(current) {
                if(current->getKey() == key) {
                    return current->getDataRef();
                }
                current = current->getNext();
            }

            throw runtime_error("Key no encontrada en la tabla hash");
        }
};

#endif