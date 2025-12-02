#pragma once
#include "Node.h"

template <typename T>
T Node<T>::getData() const {
    return data;
}

template <typename T>
T& Node<T>::getDataRef() {
    return data;
}

template <typename T>
Node<T>* Node<T>::getPrev() const {
    return prev;
}

template <typename T>
Node<T>* Node<T>::getNext() const {
    return next;
}

template <typename T>
int Node<T>::getKey() const {
    return key;
}

template <typename T>
void Node<T>::setKey(int newKey) {
    key = newKey;
}

template <typename T>
void Node<T>::setData(const T& val) {
    data = val;
}

template <typename T>
void Node<T>::setPrev(Node<T>* node) {
    prev = node;
}

template <typename T>
void Node<T>::setNext(Node<T>* node) {
    next = node;
}

template <typename U>
ostream& operator<<(ostream &os, const Node<U>& s) {
    os << s.getData();
    return os;
}