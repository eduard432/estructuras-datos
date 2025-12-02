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
Node<T>* Node<T>::getNext() const {
    return next;
}

template <typename T>
void Node<T>::setData(const T& v) {
    data = v;
}

template <typename T>
void Node<T>::setNext(Node<T>* node) {
    next = node;
}