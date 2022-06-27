#include "RedBlackTree.h"

template<class T>
TreeNode<T>::TreeNode():
        left(nullptr),
        right(nullptr),
        color(Black) {}

template<class T>
TreeNode<T>::TreeNode(T _data):
        data(_data),
        left(nullptr),
        right(nullptr),
        color(Black) {}

template<class T, class C>
RedBlackTree<T,C>::RedBlackTree(C &cmp):
    _root(nullptr),
    _cmp(cmp)
    {}

template<class T, class C>
RedBlackTree<T, C>::~RedBlackTree() {
    deleteNode(root);
}

template<class T, class C>
void RedBlackTree<T, C>::Add(T _key) {
    root = insert(root, _key);
}

template<class T, class C>
void RedBlackTree<T, C>::Delete(T _key) {
    root = erase(root, _key);
}

template<class T, class C>
void RedBlackTree<T, C>::delete_node(TreeNode<T> *node) {
    if (!node)
        return;
    delete_node(node->left);
    delete_node(node->right);
    delete node;
}