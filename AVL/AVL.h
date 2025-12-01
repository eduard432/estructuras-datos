#ifndef AVL_H
#define AVL_H

#include "Node.h"

template <typename T>
class AVL {
    private:
        Node<T>* root;

        // utils
        int height(Node<T>* n) const;
        int balanceFactor(Node<T>* n) const;
        int maxValue(const int a, const int b) const;

        // rotations
        Node<T>* rotateRight(Node<T>* node);
        Node<T>* rotateLeft(Node<T>* node);
        Node<T>* rotateRightLeft(Node<T>* node);
        Node<T>* rotateLeftRight(Node<T>* node);

        Node<T>* insert(Node<T>* node, const T& value);
        Node<T>* remove(Node<T>* node, const T& value);
        void destroy(Node<T>* node);
        void print(Node<T>* node) const;
        bool ancestors(const T& value, Node<T>* node) const;

        Node<T>* search(Node<T>* node, const T& value) const;

    public:
        AVL(): root(nullptr) {}
        ~AVL();
        void print() const;
        void clear();

        void remove(const T& value);
        void insert(const T& value);
        void ancestors(const T& value) const;

        Node<T>* search(const T& value) const;
};

#include "AVL.tpp"

#endif