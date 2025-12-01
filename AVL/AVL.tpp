#pragma once
#include "AVL.h"

template <typename T>
int AVL<T>::height(Node<T>* n) const {
    return n ? n->getHeight() : 0;
}

template <typename T>
int AVL<T>::balanceFactor(Node<T>* n) const {
    if (!n) {
        return 0;
    }

    return height(n->getLeft())
}

template <typename T>
int AVL<T>::maxValue(int a, int b) const {
    return (a > b) ? a : b;
}

