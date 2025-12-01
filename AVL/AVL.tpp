#pragma once
#include "AVL.h"
#include <iostream>

using namespace std;
// utils
template <typename T>
int AVL<T>::height(Node<T>* n) const {
    return n ? n->getHeight() : 0;
}

template <typename T>
int AVL<T>::balanceFactor(Node<T>* n) const {
    if (!n) {
        return 0;
    }

    return height(n->getLeft()) - height(n->getRight());
}

template <typename T>
int AVL<T>::maxValue(int a, int b) const {
    return (a > b) ? a : b;
}

// rotations

template <typename T>
Node<T>* AVL<T>::rotateRight(Node<T>* node) {
    Node<T>* temp = node->getLeft();
    
    node->setLeft(temp->getRight());
    temp->setRight(node);

    node->setHeight(1 + maxValue(height(node->getLeft()), height(node->getRight())));
    temp->setHeight(1 + maxValue(height(temp->getLeft()), height(temp->getRight())));

    return temp;
}

template <typename T>
Node<T>* AVL<T>::rotateLeft(Node<T>* node) {
    Node<T>* temp = node->getRight();

    node->setRight(temp->getLeft());
    temp->setLeft(node);

    node->setHeight(1 + maxValue(height(node->getLeft()), height(node->getRight)));
    temp->setHeight(1 + maxValue(height(temp->getLeft()), height(temp->getRight)));
}

template <typename T>
Node<T>* AVL<T>::rotateRightLeft(Node<T>* node) {
    node->setRight(rotateRight(node->getRight()));
    return rotateLeft(node);
}

template <typename T>
Node<T>* AVL<T>::rotateLeftRight(Node<T>* node) {
    node->setLeft(rotateLeft(node->getLeft()));
    return rotateRight(node);
}

template <typename T>
void AVL<T>::insert(const T& value) {
    root = insert(root, value);
}

template <typename T>
Node<T>* AVL<T>::insert(Node<T>* node, const T& value) {
    if(!node) {
        return new Node<T>(value);
    }

    if (value < node->getData()) {
        node->setLeft(insert(node->getLeft(), value));
    } else if(value > node->getData()) {
        node->setRight(insert(node->getRight(), value));
    } else {
        return node;
    }

    node->setHeight(1 + maxValue(height(node->getLeft()), height(node->getRight())));
    const int bf = balanceFactor(node);

    if(bf > 1 && value < node->getLeft()->getData()){
        // Se desbalanceo a la izquierda del hijo izquierdo
        return rotateRight(node);
    } else if(bf > 1 && value > node->getLeft()->getData()){
        // Se desbalanceo a la derecha del hijo izquierdo
        return rotateLeftRight(node);
    } else if(bf < -1 && value < node->getRight()->getData()) {
        // Se desbalanceo a la izquierda del hijo derecho
        return rotateRightLeft(node);
    } else if(bf < -1 && value > node->getRight()->getData()) {
        // Se desbalanceo a la derecha del hijo derecho
        return rotateLeft(node);
    }

    return node;
}

template <typename T>
Node<T>* AVL<T>::remove(Node<T>* node, const T& value) {
    if(node == nullptr) {
        return nullptr;
    }

    if(value < node->getData()) {
        node->setLeft(remove(node->getLeft(), value));
    } else if(value > node->getData()) {
        node->setRight(remove(node->getRight(), value));
    } else {
        // Nodo encontrado
        if(node->getLeft() == nullptr && node->getRight() == nullptr){
            // nodo hoja
            delete node;
            return nullptr;
        } else if(node->getLeft() == nullptr) {
            Node<T>* temp = node->getRight();
            delete node;
            return temp;
        } else if(node->getRight() == nullptr) {
            Node<T>* temp = node->getLeft();
            delete node;
            return temp;
        } else {
            Node<T>* maxNode = node->getLeft();
            while(maxNode->getRight()!=nullptr) {
                maxNode = maxNode->getRight();
            }
            node->setData(maxNode->getData());
            node->setLeft(remove(node->getLeft(), maxNode->getData()));
        }

        node->setHeight(1 + maxValue(height(node->getLeft()), height(node->getRight())));

        const int bf = balanceFactor(node);

        if(bf > 1 && balanceFactor(node->getLeft()) >= 0) {
            // Pesado hacia la izquierda
            return rotateRight(node);
        }
        if(bf < -1 && balanceFactor(node->getRight()) <= 0) {
            return rotateLeft(node);
        }
        if(bf > 1 && balanceFactor(node->getRight()) < 0) {
            return rotateLeftRight(node);
        }
        if(bf < - 1 && balanceFactor(node->getRight()) > 0) {
            return rotateRightLeft(node);
        }

    }

    return node;
}

        
template <typename T>
void AVL<T>::destroy(Node<T>* node) {


}

template <typename T>
void AVL<T>::print() const {
    print(root);
}

template <typename T>
void AVL<T>::print(Node<T>* node) const {
    if(node == nullptr) {
        return;
    }
    
    cout << "Nodo: " << node->getData() << " (Izq: ";

    if(node->getLeft()) {
        cout << node->getLeft()->getData();
    } else {
        cout << "null";
    }

    cout << ", Der: ";

    if(node->getRight()) {
        cout << node->getRight()->getData();
    }

    cout << ")" << endl;

    print(node->getLeft());
    print(node->getRight());
}

template <typename T>
void AVL<T>::ancestors(const T& value) const {
    ancestors(value, root);
}

template <typename T>
bool AVL<T>::ancestors(const T& value, Node<T>* node) const {
    if (node == nullptr) return false;

    if (value == node->getData()) return true;

    if ((value < node->getData() && ancestors(value, node->getLeft())) ||
        (value > node->getData() && ancestors(value, node->getRight()))) {

        cout << node->getData() << "->";
        return true;
    }

    return false;
}

template <typename T>
Node<T>* AVL<T>::search(const T& value) const {
    return search(root, value);
}

template <typename T>
Node<T>* AVL<T>::search(Node<T>* node, const T& value) const {
    if (node == nullptr) {
        return nullptr; // No encontrado
    }

    if (value == node->getData()) {
        return node; // Encontrado
    } 
    else if (value < node->getData()) {
        return search(node->getLeft(), value);  
    } 
    else {
        return search(node->getRight(), value);
    }
}

template <typename T>
AVL<T>::~AVL() {

}


template <typename T>
void AVL<T>::clear() {

}

template <typename T>
void AVL<T>::remove(const T& value) {

}