#include <iostream>
#include <stack>
using std::stack;
struct Int_Compare{
    bool operator()(const int&f, const int&s){
        return f>=s;
    }
};

template<class T>
struct TreeNode{
    T data;
    TreeNode * left;
    TreeNode * right;
    TreeNode();
    explicit TreeNode(T _data);
};

template<class T>
TreeNode<T>::TreeNode():
        left(nullptr),
        right(nullptr){}

template<class T>
TreeNode<T>::TreeNode(T _data):
        data(_data),
        left(nullptr),
        right(nullptr){}


template<class T, class C>
class BinaryTree{
public:
    explicit BinaryTree(C & _cmp);
    ~BinaryTree();
    void insert(T _key);
    void post_order();
private:
    void add_right(stack<TreeNode<T>*> &left_stack,stack<TreeNode<T>*> & stack, TreeNode<T> * current);
    TreeNode<T> * root;
    C cmp;
};

template<class T, class C>
BinaryTree<T,C>::BinaryTree(C & _cmp):
        root(nullptr),
        cmp(_cmp){}

template<class T, class C>
BinaryTree<T,C>::~BinaryTree(){
    if (!root)
        return;
    stack<TreeNode<T>*> left_storage;
    stack<TreeNode<T>*> storage;
    TreeNode<T>* curr = root;
    left_storage.push(curr);
    while(!left_storage.empty()){
        left_storage.pop();
        add_right(left_storage, storage,curr);
        if(!left_storage.empty())
            curr = left_storage.top();
    }
    while(!storage.empty()){
        delete storage.top();
        storage.pop();
    }
}
template<class T, class C>
void BinaryTree<T,C>::insert(T _key) {

    if(!root){
        root = new TreeNode<T>(_key);
        return;
    }
    TreeNode<T> * temp = root;
    while(true){
        if(cmp(_key,temp->data)) {
            if(temp->right)
                temp = temp->right;
            else {
                temp->right = new TreeNode<T>(_key);
                return;
            }
        } else {
            if(temp->left)
                temp = temp->left;
            else {
                temp->left = new TreeNode<T>(_key);
                return;
            }
        }
    }
}

template<class T,class C>
void BinaryTree<T,C>::add_right(stack<TreeNode<T>*> & left_stack,stack<TreeNode<T>*> & stack, TreeNode<T> * current){
    while(current){
        stack.push(current);
        if(current->left)
            left_stack.push(current->left);
        current = current->right;
    }
}

template<class T,class C>
void BinaryTree<T,C>::post_order() {
    if (!root)
        return;
    stack<TreeNode<T>*> left_storage;
    stack<TreeNode<T>*> storage;
    TreeNode<T>* curr = root;
    left_storage.push(curr);
    while(!left_storage.empty()){
        left_storage.pop();
        add_right(left_storage, storage,curr);
        if(!left_storage.empty())
            curr = left_storage.top();
    }
    while(!storage.empty()){
        std::cout << storage.top()->data << ' ';
        storage.pop();
    }
}

int main(){
    Int_Compare cmp;
    BinaryTree<int, Int_Compare> tree(cmp);
    int n;
    std::cin >> n;
    for(int i=0; i<n;i++){
        int temp;
        std::cin >> temp;
        tree.insert(temp);
    }
    tree.post_order();
    return 0;
}
