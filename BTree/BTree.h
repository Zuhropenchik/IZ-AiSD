#ifndef SELF_DEVELOPMENT_BTREE_H
#define SELF_DEVELOPMENT_BTREE_H

#include<iostream>
#include<vector>
#include<queue>

using std::vector;

template<class T>
struct TreeNode {
    bool _is_leaf;
    vector<T> keys;
    vector<TreeNode *> children;

    explicit TreeNode(bool is_leaf) : _is_leaf(is_leaf) {}

    ~TreeNode() { for (TreeNode<T> *child: children) { delete child; }}
};

template<class T, class C>
class BTree {
public:
    explicit BTree(C &cmp, size_t t) : _root(nullptr), _cmp(cmp), _max_capacity(t) {}

    ~BTree() { delete _root; }

    void Add(const T &key);

    void BFS();

private:
    TreeNode<T> *_root;
    size_t _max_capacity;
    C _cmp;

    bool is_full(TreeNode<T> *node) { return node->children.size() == 2 * _max_capacity - 1; }

    void insert_non_full(TreeNode<T> *node, const T &key);

    void split_child(TreeNode<T> *node, int index);
};


#endif //SELF_DEVELOPMENT_BTREE_H
