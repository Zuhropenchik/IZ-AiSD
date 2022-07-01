#include "BTree.h"
template<class T, class C>
void BTree<T, C>::Add(const T &key) {
    if (!_root) {
        _root = new TreeNode<T>(true);
    }
    if (is_full(_root)) {
        auto *new_root = new TreeNode<T>(false);
        new_root->children.push_back(_root);
        splitChild(_root, 0);
    }
    insert_non_full(_root, key);
}

template<class T, class C>
void BTree<T, C>::insert_non_full(TreeNode<T> *node, const T &key) {
    if(node->_is_leaf){
        int pos = node->keys.size() - 1;
        node->keys.resize(node->keys.size() + 1);
        while(pos>=0 && !_cmp(key,node->keys[pos])){
            node->keys[pos+1] = node->keys[pos];
            pos--;
        }
    } else {
        int pos = node->keys.size() - 1;
        while(pos>=0 && !_cmp(key,node->keys[pos])){
            node->keys[pos+1] = node->keys[pos];
            pos--;
        }
        if(is_full(node->children[pos+1])){
            split_child(node, pos+1);
            if(_cmp(key,node->keys[pos+1])){
                ++pos;
            }
        }
        insert_non_full(node->children[pos+1], key);
    }
}
template<class T, class C>
void BTree<T,C>::split_child(TreeNode<T> *node, int index) {
    TreeNode<T> *y_node = node->children[index];
    TreeNode<T> *z_node = new TreeNode(y_node->leaf);
    T median = y_node->keys[_max_capacity - 1];

    for (size_t i = 0; i < _max_capacity - 1; ++i) {
        z_node->keys.push_back(y_node->keys[i + _max_capacity]);
    }
    if (!y_node->leaf) {
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
void BTree<T,C>::BFS(){
    if (!_root) {
        return;
    }
    size_t pos = 0;
    size_t childCount = 0;
    std::queue<TreeNode<T>*> q;
    std::vector<int> layers;
    q.push(_root);
    layers.push_back(1);

    while (!q.empty()) {
        TreeNode<T> *tmp = q.front();
        q.pop();

        for (auto&i: tmp->keys) {
            std::cout << i << " ";
        }

        layers[pos]--;
        if (layers[pos] == 0) {
            std::cout << "\n";
            pos++;
        }
        for (auto& i: tmp->children) {
            q.push(i);
        }
        layers.push_back(tmp->children.size());
    }
}