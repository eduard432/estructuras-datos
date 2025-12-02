#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Node.h"

template <typename T>
class HashTable {
    private:
        static const int capacity = 20;
        Node<T>* table[capacity];
        int hashFunction(int key) const;
    public:
        HashTable();
        ~HashTable();
        void insert(int key, const T& value);
        bool remove(int key);
        T& search(int key) const;
        void print() const;
};

#include "HashTable.tpp"

#endif 