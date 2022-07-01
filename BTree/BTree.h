#ifndef SELF_DEVELOPMENT_BTREE_H
#define SELF_DEVELOPMENT_BTREE_H

#include<iostream>
#include<vector>
#include<queue>

using std::vector;


template<class T, class C>
class BTree {
public:
    struct TreeNode {
        bool _is_leaf;
        vector<T> keys;
        vector<TreeNode *> children;

        explicit TreeNode(bool is_leaf) : _is_leaf(is_leaf) {}

        ~TreeNode() {
            for (TreeNode *i: children)
                delete i;
        }
    };

    explicit BTree(C &cmp, size_t t) : _root(nullptr), _cmp(cmp), _max_capacity(t) {}

    ~BTree() { delete _root; }

    void Add(const T &key);

    void BFS();

private:
    TreeNode *_root;
    size_t _max_capacity;
    C _cmp;

    bool is_full(TreeNode *node) { return node->keys.size() == 2 * _max_capacity - 1; }

    void insert_non_full(TreeNode *node, const T &key);

    void split_child(TreeNode *node, int index);
};

template<class T, class C>
void BTree<T, C>::Add(const T &key) {
    if (!_root) {
        _root = new TreeNode(true);
    }

    if (is_full(_root)) {
        auto new_root = new TreeNode(false);
        new_root->children.push_back(_root);
        _root = new_root;
        split_child(_root, 0);
    }

    insert_non_full(_root, key);
}

template<class T, class C>
void BTree<T, C>::insert_non_full(TreeNode *node, const T &key) {
    int pos = node->keys.size() - 1;
    if (node->_is_leaf) {
        node->keys.resize(node->keys.size() + 1);

        while (pos >= 0 && _cmp(key, node->keys[pos])) {
            node->keys[pos + 1] = node->keys[pos];
            pos--;
        }
        node->keys[pos + 1] = key;

    } else {
        while (pos >= 0 && _cmp(key, node->keys[pos])) {
            pos--;
        }

        if (is_full(node->children[pos + 1])) {
            split_child(node, pos + 1);


            if (_cmp(node->keys[pos + 1], key))
                pos++;
        }
        insert_non_full(node->children[pos + 1], key);
    }
}

template<class T, class C>
void BTree<T, C>::split_child(TreeNode *node, int index) {
    TreeNode *y_node = node->children[index];
    auto z_node = new TreeNode(y_node->_is_leaf);
    T median = y_node->keys[_max_capacity - 1];

    for (size_t i = 0; i < _max_capacity - 1; ++i) {
        z_node->keys.push_back(y_node->keys[i + _max_capacity]);
    }
    if (!y_node->_is_leaf) {
        for (size_t i = 0; i < _max_capacity; ++i) {
            z_node->children.push_back(y_node->children[i + _max_capacity]);
        }
        y_node->children.resize(_max_capacity);
    }
    y_node->keys.resize(_max_capacity - 1);

    node->children.resize(node->children.size() + 1);
    for (size_t i = node->children.size() - 1; i > index + 1; --i) {
        node->children[i] = node->children[i - 1];
    }
    node->children[index + 1] = z_node;

    node->keys.resize(node->keys.size() + 1);
    for (size_t i = node->keys.size() - 1; i > index; --i) {
        node->keys[i] = node->keys[i - 1];
    }
    node->keys[index] = median;
}

template<class T, class C>
void BTree<T, C>::BFS() {
    if (!_root) {
        return;
    }
    size_t pos = 0;
    size_t childCount = 0;
    std::queue<TreeNode *> q;
    std::vector<int> layers;
    q.push(_root);
    layers.push_back(1);

    while (!q.empty()) {
        TreeNode *tmp = q.front();
        q.pop();

        for (auto i: tmp->keys) {
            std::cout << i << " ";
        }

        layers[pos]--;
        if (layers[pos] == 0) {
            std::cout << "\n";
            pos++;
        }
        for (auto i: tmp->children) {
            q.push(i);
        }
        layers.push_back(tmp->children.size());
    }
}

#endif //SELF_DEVELOPMENT_BTREE_H
