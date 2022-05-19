#include <iostream>
#include <stack>

using std::stack;

struct Int_Compare {
    bool operator()(const int &f, const int &s) {
        return f >= s;
    }
};

template<class T>
struct TreeNode {
    T data;
    TreeNode *left;
    TreeNode *right;
    int height;

    TreeNode();

    explicit TreeNode(T _data);
};

template<class T>
TreeNode<T>::TreeNode():
        left(nullptr),
        right(nullptr),
        height(1) {}

template<class T>
TreeNode<T>::TreeNode(T _data):
        data(_data),
        left(nullptr),
        right(nullptr),
        height(1) {}


template<class T, class C>
class BinaryTree {
public:
    explicit BinaryTree(C &_cmp);

    ~BinaryTree();


    void Add(T _key);
    void Delete(T _key);
    T findKStatI(int k);

    T findKStat(TreeNode<T> *node, int k, int curr_stat);

private:
    void deleteNode(TreeNode<T> * node);
    int getHeight(TreeNode<T> *node);
    void fixHeight(TreeNode<T> *node);
    int balance_factor(TreeNode<T> *node);
    TreeNode<T> *insert(TreeNode<T> *node, T _key);


    TreeNode<T> *leftRotate(TreeNode<T> *node);
    TreeNode<T> *rightRotate(TreeNode<T> *node);
    TreeNode<T> *Balancing(TreeNode<T> *node);

    TreeNode<T> *erase(TreeNode<T> *node, T _key);
    TreeNode<T> * findMin(TreeNode<T> *node);
    TreeNode<T> * eraseMin(TreeNode<T> *node);

    int left_count(TreeNode<T> *node);
    int right_count(TreeNode<T> *node);
    int count(TreeNode<T> *node);

    TreeNode<T> *root;
    C cmp;
};


template<class T, class C>
BinaryTree<T, C>::BinaryTree(C &_cmp):
        root(nullptr),
        cmp(_cmp) {}

template<class T, class C>
BinaryTree<T, C>::~BinaryTree(){
    deleteNode(root);
}

template<class T, class C>
void BinaryTree<T, C>::Add(T _key){
    root = insert(root, _key);
}

template<class T, class C>
void BinaryTree<T, C>::Delete(T _key){
    root = erase(root, _key);
}

template<class T, class C>
T BinaryTree<T, C>::findKStatI(int k){
    return findKStat(root, k, 0);
}


template<class T, class C>
void BinaryTree<T,C>::deleteNode(TreeNode<T> *node){
    if(!node)
        return;
    deleteNode(node->left);
    deleteNode(node->right);
    delete node;
}

template<class T, class C>
TreeNode<T> *BinaryTree<T, C>::insert(TreeNode<T> *node, T _key) {

    if (!node) {
        return new TreeNode<T>(_key);
    }
    if (_key < node->data)
        node->left = insert(node->left, _key);
    else
        node->right = insert(node->right, _key);
    return Balancing(node);
}

template<class T, class C>
TreeNode<T> * BinaryTree<T, C>::findMin(TreeNode<T> *node){
    if(!node)
        return nullptr;
    else if(!node->left)
        return node;
    else
        return findMin(node->left);
}

template<class T, class C>
TreeNode<T> * BinaryTree<T, C>::eraseMin(TreeNode<T> *node){
    if(!node->left)
        return node->right;
    node->left = eraseMin(node->left);
    return Balancing(node);
}

template<class T, class C>
TreeNode<T> *BinaryTree<T, C>::erase(TreeNode<T> *node, T _key) {
    if(!node)
        return nullptr;
    if(_key < node->data)
        node->left = erase(node->left,_key);
    else if(_key > node->data)
        node->right = erase(node->right,_key);
    else
    {
        if(!node->right) return node->left;
        TreeNode<T> * min = findMin(node->right);
        min->right = eraseMin(node->right);
        min->left = node->left;
        delete node;
        return Balancing(min);
    }
    return Balancing(node);
}


template<class T, class C>
int BinaryTree<T, C>::getHeight(TreeNode<T> *node) {
    if (!node)
        return 0;
    return node->height;
}

template<class T, class C>
void BinaryTree<T, C>::fixHeight(TreeNode<T> *node) {
    if (!node)
        return;
    node->height = std::max(getHeight(node->left), getHeight(node->right));
}

template<class T, class C>
int BinaryTree<T, C>::balance_factor(TreeNode<T> *node) {
    if (!root)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

template<class T, class C>
TreeNode<T> *BinaryTree<T, C>::leftRotate(TreeNode<T> *node) {
    if (!node)
        return nullptr;
    TreeNode<T> *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    fixHeight(node);
    fixHeight(temp);
    return temp;
}

template<class T, class C>
TreeNode<T> *BinaryTree<T, C>::rightRotate(TreeNode<T> *node) {
    if (!node)
        return nullptr;
    TreeNode<T> *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    fixHeight(node);
    fixHeight(temp);
    return temp;
}

template<class T, class C>
TreeNode<T> *BinaryTree<T, C>::Balancing(TreeNode<T> *node) {
    if (!node)
        return nullptr;
    int bf = balance_factor(node);
    fixHeight(node);
    if (bf == 2) {
        if (balance_factor(node->right) < 0)
            node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    if (bf == -2) {
        if (balance_factor(node->left) > 0)
            node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    return node;
}

template<class T, class C>
int BinaryTree<T, C>::left_count(TreeNode<T> *node) {
    if (!node)
        return 0;
    return count(node->left);
}

template<class T, class C>
int BinaryTree<T, C>::right_count(TreeNode<T> *node) {
    if (!node)
        return 0;
    return count(node->right);
}

template<class T, class C>
int BinaryTree<T, C>::count(TreeNode<T> *node) {
    if (!node)
        return 0;
    return left_count(node) + right_count(node) + 1;
}

template<class T, class C>
T BinaryTree<T, C>::findKStat(TreeNode<T> *node, int k, int curr_stat) {
    if (!node)
        return -1;
    int curr = curr_stat + left_count(node);
    if (curr == k) {
        return node->data;
    }
    if (curr > k) {
        return findKStat(node->left, k, curr_stat);
    }
    return findKStat(node->right, k, curr + 1);
}

int main() {
    Int_Compare cmp;
    BinaryTree<unsigned int, Int_Compare> tree(cmp);
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int temp, kstat;
        std::cin >> temp >> kstat;
        if (temp > 0) {
            tree.Add(temp);
        }
        if (temp < 0)
            tree.Delete(-1* temp);
        std::cout << tree.findKStatI(kstat) << ' ';
    }
    return 0;
}
